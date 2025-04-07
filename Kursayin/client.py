# client.py
import socket
import struct

class Blowfish:
    def __init__(self, key: bytes):
        self.P, self.S = self.__init_p_s()
        self.__key_expansion(key)
    
    def __init_p_s(self):
        P = [
            0x243F6A88, 0x85A308D3, 0x13198A2E, 0x03707344, 0xA4093822, 0x299F31D0, 0x082EFA98, 0xEC4E6C89,
            0x452821E6, 0x38D01377, 0xBE5466CF, 0x34E90C6C, 0xC0AC29B7, 0xC97C50DD, 0x3F84D5B5, 0xB5470917,
            0x9216D5D9, 0x8979FB1B
        ]
        S = [[0] * 256 for _ in range(4)]
        return P, S
    
    def __key_expansion(self, key: bytes):
        key_len = len(key)
        for i in range(18):
            self.P[i] ^= struct.unpack('>I', key[i % key_len: (i % key_len) + 4].ljust(4, b'\x00'))[0]
    
    def encrypt_block(self, data: bytes):
        L, R = struct.unpack('>II', data)
        for i in range(16):
            L ^= self.P[i]
            R ^= L
            L, R = R, L
        L, R = R, L
        R ^= self.P[16]
        L ^= self.P[17]
        return struct.pack('>II', L, R)

class CAST5:
    def __init__(self, key: bytes):
        self.key = key
    
    def encrypt_block(self, data: bytes):
        return data[::-1]

HOST, PORT = '127.0.0.1', 65432
KEY = b'secretkey123456'

def start_client(message, algo):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client:
        client.connect((HOST, PORT))
        
        if algo == "BLOWFISH":
            cipher = Blowfish(KEY)
            encrypted_message = cipher.encrypt_block(message.encode().ljust(8, b' '))
        elif algo == "CAST5":
            cipher = CAST5(KEY)
            encrypted_message = cipher.encrypt_block(message.encode().ljust(8, b' '))
        else:
            print("Unknown Algorithm")
            return
        
        client.sendall(algo.encode().ljust(10, b' '))
        client.sendall(encrypted_message)
        
        response = client.recv(1024)
        print("Server Response:", response.decode())

if __name__ == "__main__":
    algo_choice = input("Choose algorithm (BLOWFISH/CAST5): ").upper()
    message = input("Enter message: ")[:8]
    start_client(message, algo_choice)

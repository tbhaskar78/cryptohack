from pwn import * # pip install pwntools
import json
import sys

r = remote('socket.cryptohack.org', 13377, level = 'debug')

def json_recv():
    line = r.recvline()
    return json.loads(line.decode())

def json_send(hsh):
    request = json.dumps(hsh).encode()
    r.sendline(request)


received = json_recv()

print("Received type: ")
print(received["type"])
print("Received encoded value: ")
print(received["encoded"])
x = raw_input ("Enter decoded : ")
x = x.decode("utf-8") 
x = x.strip('\n')


to_send = {
    "decoded": x
}
print(to_send)
json_send(to_send)

json_recv()


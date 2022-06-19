import socket

# Create a socket object
s = socket.socket()

# Define the port on which you want to connect
port = 8826

# connect to the server on local computer
s.connect(('127.0.0.1', port))

s.sendall(b'hello')
# receive data from the server and decoding to get the string.
print(s.recv(1024).decode())

# login:
s.sendall(b'21000{"username": "user1", "password": "1234"}')
print(s.recv(1024).decode())

# signup:
s.sendall(b'11000{"username": "user1", "password": "1234", "email": "user1@gmail.com"}')
temp=s.recv(1024)
#temp[0]= int.from_bytes(temp[0], "big")

print(temp)

# close the connection
s.close()

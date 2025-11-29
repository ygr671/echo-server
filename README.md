# echo-server

🇫🇷  
echo-server est un petit serveur TCP écrit en C. Il écoute sur le port 7777, accepte un client à la fois et renvoie ses messages. Le serveur envoie un message de bienvenue, un prompt "[COMMAND]" à chaque tour, puis renvoie les messages via "[SERVER] <message>". Deux commandes sont reconnues : "exit" pour déconnecter le client, et "shutdown" pour arrêter complètement le serveur. Le but du projet est surtout de manipuler les sockets POSIX et de comprendre la structure d’un serveur minimaliste.

🇬🇧  
echo-server is a small TCP server written in C. It listens on port 7777, accepts one client at a time and echoes messages back. The server sends a welcome message, a "[COMMAND]" prompt on each loop, and replies using "[SERVER] <message>". Two commands are supported: "exit" to disconnect the client, and "shutdown" to stop the server entirely. The project mainly serves as a small exercise to practice POSIX sockets and basic server structure.

# Fonctionnalités / Features

🇫🇷  
- écoute sur le port 7777  
- un seul client simultané  
- message de bienvenue  
- prompt "[COMMAND]"  
- echo "[SERVER] <message>"  
- commande "exit"  
- commande "shutdown"  
- logs simples

🇬🇧  
- listens on port 7777  
- single client at a time  
- welcome message  
- "[COMMAND]" prompt  
- "[SERVER] <message>" echo  
- "exit" command  
- "shutdown" command  
- simple server logs

# Compilation / Building

🇫🇷  
gcc server.c -o server  
./server

🇬🇧  
gcc server.c -o server  
./server

# Notes

🇫🇷  
Projet simple, non destiné à un usage réel.

🇬🇧  
Simple project, not intended for real-world use.

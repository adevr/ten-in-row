all:
	gcc -o moderator/moderator moderator/Moderator.c moderator/main.c
	gcc -o client/client client/Client.c client/main.c
	gcc -o teninrow main.c

arbitro:
	gcc -o moderator/moderator moderator/Moderator.c moderator/main.c

cliente:
	gcc -o client/client client/Client.c client/main.c

jogo:
	gcc -o application/game application/Jogo.c application/main.c

clean:
	rm application/Jogo
	rm client/client
	rm moderator/moderator
	rm teninrow
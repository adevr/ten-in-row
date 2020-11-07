all:
	gcc -o moderator/moderator moderator/Arbitro.c moderator/main.c
	gcc -o client/client client/Cliente.c client/main.c
	gcc -o teninrow main.c

clean:
	$(RM) client/client
	$(RM) moderator/moderator
	$(RM) teninrow
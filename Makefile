all:
	dd if=/dev/zero of=sharedfile count=10 bs=10
	cc reciever.c -o receive
	cc sender.c -o sender

clean: 
	rm -rf receive
	rm -rf sender
	rm -rf sharedfile

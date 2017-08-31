mmap_addr:
	gcc mmap_addr.c -o mmap_addr -g
	./mmap_addr

mmap_data:
	gcc mmap_data.c -o mmap_data -g
	./mmap_data

child_parent_mutex_anony:
	gcc child_parent_mutex_anony.c -o child_parent_mutex_anony -lpthread -g
	./child_parent_mutex_anony

child_parent_mutex_fopen:
	gcc child_parent_mutex_fopen.c -o child_parent_mutex_fopen -lpthread -g
	./child_parent_mutex_fopen

multi:
	./multi_process_a &
	./multi_process_b

multi_reverse:
	./multi_process_b &
	./multi_process_a

multi_process_all: multi_process_a multi_process_b

multi_process_a:
	gcc multi_process_a.c -o multi_process_a -lpthread -g

multi_process_b:
	gcc multi_process_b.c -o multi_process_b -lpthread -g

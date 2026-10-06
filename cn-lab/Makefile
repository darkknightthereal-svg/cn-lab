CC     = gcc
CFLAGS = -Wall
DIRS   = exp6_udp_translator exp8_udp_time_server exp9_tcp_file_server
PROGS  = $(foreach d,$(DIRS),$(d)/server $(d)/client)

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(PROGS)

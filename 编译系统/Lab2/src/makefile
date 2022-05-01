CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -std=c99

CFILES = $(shell find ./ -name "*.c")
OBJS = $(CFILES:.c=.o)
LFILE = $(shell find ./ -name "*.l")
YFILE = $(shell find ./ -name "*.y")
LFC = $(shell find ./ -name "*.l" | sed s/[^/]*\\.l/lex.yy.c/)
YFC = $(shell find ./ -name "*.y" | sed s/[^/]*\\.y/syntax.tab.c/)
LFO = $(LFC:.c=.o)
YFO = $(YFC:.c=.o)

parser: syntax $(filter-out $(LFO),$(OBJS))
	$(CC) -o parser $(filter-out $(LFO),$(OBJS)) -lfl

syntax: lexical syntax-c
	$(CC) -c $(YFC) -o $(YFO)

lexical: $(LFILE)
	$(FLEX) -o $(LFC) $(LFILE)

syntax-c: $(YFILE)
	$(BISON) -o $(YFC) -d -v $(YFILE)

-include $(patsubst %.o, %.d, $(OBJS))

.PHONY: clean test
test:
	./parser ../test/1.cmm
	./parser ../test/2.cmm
	./parser ../test/3.cmm
	./parser ../test/4.cmm
	./parser ../test/5.cmm
	./parser ../test/6.cmm
	./parser ../test/7.cmm
	./parser ../test/8.cmm
	./parser ../test/9.cmm
	./parser ../test/10.cmm
	./parser ../test/11.cmm
	./parser ../test/12.cmm
	./parser ../test/13.cmm
	./parser ../test/14.cmm
	./parser ../test/15.cmm
	./parser ../test/16.cmm
	./parser ../test/17.cmm
	./parser ../test/18.cmm
clean:
	rm -f parser lex.yy.c syntax.tab.c syntax.tab.h syntax.output
	rm -f $(OBJS) $(OBJS:.o=.d)
	rm -f $(LFC) $(YFC) $(YFC:.c=.h)
	rm -f *~
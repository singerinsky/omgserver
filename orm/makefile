
PROTO_FILE_LIST=$(shell ls *.proto |grep -v server)

.PHONY:all cpp python as
all : cpp python as

cpp : 
	protoc --cpp_out=./ *.proto                       

clean :
	@find . -name "*.pb.cc" -exec rm -f {} \;
	@find . -name "*.pb.h" -exec rm -f {} \;
-include  $(DEPS)


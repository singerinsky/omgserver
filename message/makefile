
PROTO_FILE_LIST=$(shell ls *.proto |grep -v server)

.PHONY:all cpp python as
all : cpp python as

cpp : 
	protoc --cpp_out=../net *.proto                       
python :
	protoc --python_out=python *.proto                       
as : 
	protoc  --plugin=protoc-gen-as3 --as3_out=as3 $(PROTO_FILE_LIST)

clean :
	@find . -name "*.as" -exec rm -f {} \;
	@find . -name "*.pb.cc" -exec rm -f {} \;
	@find . -name "*.pb.h" -exec rm -f {} \;
	@find . -name "*.py" -exec rm -f {} \;
-include  $(DEPS)


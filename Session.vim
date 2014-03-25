let SessionLoad = 1
if &cp | set nocp | endif
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd ~/workspace/omgserver
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +114 db_server/main.cpp
badd +145 db_server/CDBMsgDispatcher.cpp
badd +1 ~/workspace/omgserver/db_server/main.h
badd +31 net/epoll_handler.cpp
badd +10 ~/workspace/omgserver/net/epoll_handler.h
badd +20 common/server_global.h
badd +7 common/singleton.h
badd +24 db_server/CDBMsgDispatcher.h
badd +66 common/time_util.h
badd +5 ~/workspace/omgserver/common/singleton.cpp
badd +1 ~/workspace/omgserver/common/server_global.c
badd +1 common/server_global.cpp
badd +140 common/timer_manager.cpp
badd +20 common/server_application.h
badd +24 db_server/CServerManage.h
badd +18 db_server/DBAccepter.cpp
badd +18 ~/workspace/omgserver/db_server/DBAccepter.h
badd +64 ~/workspace/omgserver/db_server/CServerManage.cpp
badd +101 net/socketclient.cpp
args db_server/main.cpp
edit db_server/main.cpp
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
let s:l = 78 - ((18 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
78
normal! 0
if exists('s:wipebuf')
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToO
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :

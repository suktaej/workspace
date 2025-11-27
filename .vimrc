let mapleader = " "

nnoremap <leader>d "_d
vnoremap <leader>d "_d
vnoremap <leader>p "_dP

nnoremap <leader>c :call ToggleBool()<CR>

inoremap ,, <Esc>
inoremap <C-h> <Left>
inoremap <C-j> <Down>
inoremap <C-k> <Up>
inoremap <C-l> <Right>
inoremap <C-w> <BS>

function! ToggleBool()
    let w = expand('<cword>')
    if w ==# 'true'
        execute 'normal! ciwfalse'
    elseif w ==# 'false'
        execute 'normal! ciwtrue'
    endif
endfunction
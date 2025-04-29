"Default vimrc setting
if has("syntax")
	syntax on
endif

set number
set relativenumber
set ruler
set title

set cindent
set autoindent
set smartindent

set tabstop=4
set shiftwidth=4
set softtabstop=4
"set smarttab
"set expandtab

set hlsearch
set ignorecase
set smartcase
set showmatch
set cursorline

set laststatus=2
set statusline=%F\ %y%m%r\ %=Line:\ %l/%L\ [%p%%]\ Col:%c\ Buf:%n

set mouse=a

set clipboard+=unnamedplus

augroup highlight_yank
	autocmd!
	autocmd TextYankPost * silent! lua vim.highlight.on_yank()
augroup END

let mapleader = " "

" Leader + s를 눌렀을 때 'true'와 'false'를 토글
nnoremap <Leader>s :call ToggleTrueFalse()<CR>

function! ToggleTrueFalse()
    " 현재 커서 위치에서 'true' 또는 'false'를 찾고 바꿉니다.
    let line = getline('.')
    let col = col('.') - 1
    let word = matchstr(line, '\%'.col.'c\w*')

    if word == "true"
        " 'true'를 'false'로 바꿉니다.
        execute 'normal! ciwfalse'
    elseif word == "false"
        " 'false'를 'true'로 바꿉니다.
        execute 'normal! ciwtrue'
    endif
endfunction

nnoremap <Leader>h ^
vnoremap <Leader>h v^
nnoremap <Leader>l $
vnoremap <Leader>l v$
nnoremap <Leader>d \"_d
nnoremap <Leader>a GVgg
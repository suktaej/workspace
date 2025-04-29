set nocompatible
filetype off

call plug#begin('~/.vim/plugged')
Plug 'scrooloose/nerdtree'
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
Plug 'thaerkh/vim-indentguides'
Plug 'preservim/nerdcommenter'
Plug 'osyo-manga/vim-anzu'
Plug 'majutsushi/tagbar'
Plug 'blueyed/vim-diminactive'
Plug 'xolox/vim-misc'
Plug 'xolox/vim-easytags'
Plug 'frazrepo/vim-rainbow'
Plug 'tpope/vim-surround'
Plug 'Raimondi/delimitMate'
Plug 'majutsushi/tagbar'
Plug 'easymotion/vim-easymotion'
Plug 'terryma/vim-multiple-cursors'
Plug 'chrisbra/NrrwRgn'
Plug 'pangloss/vim-simplefold'
Plug 'psliwka/vim-smoothie'
Plug 'tommcdo/vim-lion'
Plug 'vim-scripts/VisIncr'
"Syntax
Plug 'vim-syntastic/syntastic' 
Plug 'SirVer/ultisnips'
Plug 'Valloric/YouCompleteMe'
Plug 'mattn/emmet-vim'
"Github
Plug 'airblade/vim-gitgutter'
Plug 'tpope/vim-fugitive'
"Colorscheme
Plug 'morhetz/gruvbox'
Plug 'folke/tokyonight.nvim'
Plug 'altercation/vim-colors-solarized'
Plug 'Mofiqul/vscode.nvim'
Plug 'nanotech/jellybeans.vim'
"ETC
"Plug 'ctrlpvim/ctrlp.vim'
"Plug 'antoinemadec/vim-verilog-instance'
"Plug 'vim-scripts/Quich-Filter'
call plug#end()

filetype indent on

" Syntastic
set statusline+=%#warningmsg#
set statusline+=%{SyntasticStatuslineFlag()}
set statusline+=%*

let g:syntastic_always_populate_loc_list = 1
let g:syntastic_auto_loc_list = 1
let g:syntastic_check_on_open = 1
let g:syntastic_check_on_wq = 0

let g:syntastic_cpp_compiler = 'g++'
let g:syntastic_cpp_compiler_options = "-std=c++11 -Wall -Wextra -Wpedantic"
let g:syntastic_c_compiler_options = "-std=c11 -Wall -Wextra -Wpedantic"

" Youcompleteme
let g:ycm_global_ycm_extra_conf = '~/.vim/plugged/YouCompleteMe/third_party/ycmd/.ycm_extra_conf.py'
let g:ycm_autoclose_preview_window_after_completion = 1
let g:ycm_key_invoke_completion = '<c-space>'

" emmet-vim
let g:user_emmet_install_global = 0
autocmd FileType html,css EmmetInstall
let g:user_emmet_leader_key='<C-T>'

" delimitMate
let delimitMate_expand_cr=1

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

" Leader + h를 눌렀을 때 ^로 이동
nnoremap <Leader>h ^
" Leader + l을 눌렀을 때 $로 이동
nnoremap <Leader>l $

colorscheme jellybeans
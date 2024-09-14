" :PlugInstall
call plug#begin()
Plug 'dense-analysis/ale'
Plug 'vim-airline/vim-airline'
Plug 'nvim-tree/nvim-tree.lua'
Plug 'nvim-tree/nvim-web-devicons'
Plug 'neovim/nvim-lspconfig'
Plug 'nvim-treesitter/nvim-treesitter'
Plug 'neoclide/coc.nvim', {'branch': 'release'}
call plug#end()

set colorcolumn=120
colorscheme e1c411f
let g:airline_theme='e1c411f'

let g:airline#extensions#tabline#enabled = 1
let g:airline#extensions#tabline#show_tabs = 1
let g:airline#extensions#tabline#show_buffers = 0
let g:airline#extensions#tabline#show_tab_count = 2
let g:airline#extensions#tabline#tab_nr_type = 1 " tab number
let g:airline#extensions#tabline#show_tab_type = 0
let g:airline#extensions#tabline#formatter = 'unique_tail'

let g:ale_fixers = {'cpp': ['clang-format',]}
let g:ale_cpp_cc_options = '-Isrc'
let g:ale_fix_on_save = 1

set incsearch
set hlsearch
set ignorecase
noremap n nzz
noremap N Nzz

nnoremap <silent> <Esc><Esc> :let @/ = ""<CR>

inoremap <silent><expr> <TAB>
  \ coc#pum#visible() ? coc#pum#next(1) :
  \ Check_backspace() ? "\<Tab>" :
  \ coc#refresh()
function! Check_backspace() abort
  let col = col('.') - 1
  return !col || getline('.')[col - 1] =~# '\s'
endfunction

set wildmenu
set noshowmode

set t_Co=256

set tabstop=2
set shiftwidth=2
set expandtab

nnoremap Y y$

set scrolloff=3

set number

set noerrorbells
set visualbell

nnoremap <C-s> :w<CR>
inoremap <C-s> <Esc>:w<CR>

nnoremap <F10> :echo "hi<" . synIDattr(synID(line("."),col("."),1),"name") . '> trans<'
      \ . synIDattr(synID(line("."),col("."),0),"name") . "> lo<"
      \ . synIDattr(synIDtrans(synID(line("."),col("."),1)),"name") . ">"<CR>

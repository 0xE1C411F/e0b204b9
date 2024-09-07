" Vim color file
" Maintainer:	0xE1C411F
" Last Change:	2024 Sep 07

hi clear Normal
set background=dark

" Remove all existing highlighting and set the defaults.
hi clear

" Load the syntax highlighting defaults, if it's enabled.
if exists("syntax_on")
  syntax reset
endif

let colors_name = "e1c411f"


hi Statement          ctermfg=14              cterm=none
hi LineNr             ctermfg=8               cterm=none
hi Comment            ctermfg=2               cterm=none
hi PreProc            ctermfg=10              cterm=none
hi Constant           ctermfg=6               cterm=none
hi Identifier         ctermfg=6               cterm=italic

hi Function           ctermfg=12              cterm=none
hi Type               ctermfg=12              cterm=italic

hi cStorageClass      ctermfg=13              cterm=none

hi cppNamespace       ctermfg=4               cterm=none
hi NormalFloat                    ctermbg=8   
hi cppAttribute       ctermfg=11
hi CocFloating                    ctermbg=8

hi link cppSTLfunction Function
hi link cInclude Comment
hi link cIncluded PreProc

" :so $VIMRUNTIME/syntax/hitest.vim
" vim: sw=2

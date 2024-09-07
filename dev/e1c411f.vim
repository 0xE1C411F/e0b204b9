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


hi Statement          ctermfg=cyan                cterm=none
hi LineNr             ctermfg=darkgrey            cterm=none
hi Comment            ctermfg=darkgreen           cterm=none
hi PreProc            ctermfg=green               cterm=none
hi Constant           ctermfg=darkcyan            cterm=none
hi Identifier         ctermfg=darkcyan            cterm=italic

hi Function           ctermfg=blue                cterm=none
hi Type               ctermfg=darkblue            cterm=italic

hi cStorageClass      ctermfg=magenta             cterm=none


hi link cppSTLfunction Function
hi link cppSTLnamespace Function
hi link cInclude Comment
hi link cIncluded PreProc


" :so $VIMRUNTIME/syntax/hitest.vim
" vim: sw=2

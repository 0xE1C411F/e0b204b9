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

hi WinSeparator            ctermfg=8   ctermbg=8
hi ColorColumn                         ctermbg=8   cterm=none
hi EndOfBuffer             ctermfg=0 

hi Statement               ctermfg=14              cterm=none
hi LineNr                  ctermfg=8               cterm=none
hi Comment                 ctermfg=2               cterm=none
hi PreProc                 ctermfg=10              cterm=none
hi Constant                ctermfg=6               cterm=none
hi Identifier              ctermfg=6               cterm=italic

hi Function                ctermfg=12              cterm=none
hi Type                    ctermfg=12              cterm=italic

hi cStorageClass           ctermfg=13              cterm=none

hi cppNamespace            ctermfg=4               cterm=none
hi NormalFloat                         ctermbg=8   
hi cppAttribute            ctermfg=11
hi CocFloating                         ctermbg=8

hi NvimTreeGitDeletedIcon  ctermfg=9
hi NvimTreeGitDirtyIcon    ctermfg=3
hi NvimTreeGitIgnoredIcon  ctermfg=7
hi NvimTreeGitMergeIcon    ctermfg=10
hi NvimTreeGitNewIcon      ctermfg=10
hi NvimTreeGitRenamedIcon  ctermfg=3
hi NvimTreeGitStagedIcon   ctermfg=6

augroup HIGHLIGHT_TABLINE
  autocmd!
  autocmd User AirlineAfterInit hi airline_tab             ctermfg=7   ctermbg=8
  autocmd User AirlineAfterInit hi airline_tab_right       ctermfg=7   ctermbg=8
  autocmd User AirlineAfterInit hi airline_tabmod_unsel    ctermfg=7   ctermbg=8
  autocmd User AirlineAfterInit hi airline_tabfill         ctermfg=7   ctermbg=8

  autocmd User AirlineAfterInit hi airline_tabsel          ctermfg=15  ctermbg=4
  autocmd User AirlineAfterInit hi airline_tabsel_right    ctermfg=15  ctermbg=4
  autocmd User AirlineAfterInit hi airline_tabmod          ctermfg=15  ctermbg=4
  autocmd User AirlineAfterInit hi airline_tabmod_right    ctermfg=15  ctermbg=4
augroup END

hi link cppSTLfunction Function
hi link cInclude Comment
hi link cIncluded PreProc
" :so $VIMRUNTIME/syntax/hitest.vim
" vim: sw=2

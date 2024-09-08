vim.cmd [[source ~/.vimrc]]

vim.g.loaded_netrw = 1
vim.g.loaded_netrwPlugin = 1

require("nvim-tree").setup {
  hijack_cursor = true,
  renderer = {
    indent_markers = {
      enable = true,
      inline_arrows = false,
    },
    icons = {
      glyphs = {
        git = {
          unstaged = "m",
          renamed = "r",
          untracked = "u",
          deleted = "d",
          staged = "s",
        },
      },
    },
  },
}
vim.cmd [[nmap <F2> :NvimTreeFocus<CR>]]
vim.cmd [[imap <F2> <Esc>:NvimTreeFocus<CR>]]

vim.cmd [[nmap <F4> :NvimTreeToggle<CR>]]
vim.cmd [[imap <F4> <Esc>:NvimTreeToggle<CR>]]

vim.cmd [[autocmd VimEnter * NvimTreeOpen]]
vim.cmd [[autocmd VimEnter * wincmd p]]
vim.cmd [[command Q qa]]
vim.cmd [[command Qw wqa]]

require("lspconfig").clangd.setup{}

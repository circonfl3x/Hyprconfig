local keymap = vim.keymap
local conf = function()
local telescope=require('telescope').setup{
  defaults = {
    -- Default configuration for telescope goes here:
    -- config_key = value,
    mappings = {
      i = {
        -- map actions.which_key to <C-h> (default: <C-/>)
        -- actions.which_key shows the mappings for your picker,
        -- e.g. git_{create, delete, ...}_branch for the git_branches picker
        ["<C-h>"] = "which_key",
	["<C-j>"] = "move_selection_next",
	["<C-k>"] = "move_selection_previous"
      }
    }
  },
  pickers = {
    -- Default configuration for builtin pickers goes here:
    -- picker_name = {
    --   picker_config_key = value,
    --   ...
    -- }
    -- Now the picker_config_key will be applied every time you call this
    -- builtin picker
  },
  extensions = {
    -- Your extension configuration goes here:
    -- extension_name = {
    --   extension_config_key = value,
    -- }
    -- please take a look at the readme of the extension you want to configure
  }
}
end

return {
    'nvim-telescope/telescope.nvim', 
    tag = '0.1.8',
    lazy = false,
    dependencies = { 'nvim-lua/plenary.nvim' },
    config = conf,
    keys={
	keymap.set("n", "<leader>fk", ":Telescope keymaps<CR>"),
	keymap.set("n", "<leader>fh", ":Telescope help_tags<CR>"),
	keymap.set("n", "<leader>ff", ":Telescope find_files<CR>"),
	keymap.set("n", "<leader>fa", ":Telescope <CR>"),
	keymap.set("n", "<leader>fg", ":Telescope live_grep<CR>"),
	keymap.set("n", "<leader>fb", ":Telescope buffers<CR>"),
    },

}



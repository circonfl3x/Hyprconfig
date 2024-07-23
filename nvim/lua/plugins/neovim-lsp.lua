
local config = function()
	local lspconfig = require('lspconfig')


	--Rust
	lspconfig.rust_analyzer.setup {
  		-- Server-specific settings. See `:help lspconfig-setup`
  		settings = {
		['rust-analyzer'] = {},
  		},
	}
	end


return{
	
    "neovim/nvim-lspconfig",
    config = lspconfig,
    lazy = false,
    dependecies = {
    	"windwp/nvim-autopairs",
	"williamboman/meson.nvim",
	"creativenull/efmls-configs-nvim",
    }
}

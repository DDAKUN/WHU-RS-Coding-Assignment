const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
  lintOnSave: false,
  pluginOptions: {
    windicss: {
      // 具体配置请查看 https://github.com/windicss/vite-plugin-windicss/blob/main/packages/plugin-utils/src/options.ts
    }
  },
  configureWebpack: {
    externals: {
      BMap: "BMap",
      BMap_Symbol_SHAPE_POINT: "BMap_Symbol_SHAPE_POINT",
    },
  },
})

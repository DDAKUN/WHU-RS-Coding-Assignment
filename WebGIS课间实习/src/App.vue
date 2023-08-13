<template>
  <div id="app">
    <el-container>
      <el-header>
        <el-row>
          <el-col :span="4">
            <div class='flex inline-block justify-center items-center bg-blue-500 h-60.5px'>
              <img src="../public/img/地理信息平台.svg" width="40px" height="40px">
              <div>
                <h1 class="text-light-500 font-bold text-2xl">
                  地理信息购物平台
                </h1>
              </div>
            </div>
          </el-col>
          <el-col :span="20">
            <div>
              <el-menu mode="horizontal" background-color="#3b82f6" text-color="#f2f2f2" active-text-color="#1e3a8a" unique-opened router>
                <el-menu-item index="/Map">地图选点</el-menu-item>
                <el-submenu index="2">
                  <template slot="title">购物功能</template>
                  <el-menu-item index="Shoppingcart">购物车</el-menu-item>
                  <el-menu-item index="Goods">商品界面</el-menu-item>
                  <el-menu-item index="China">地图浏览</el-menu-item>
                </el-submenu>
                <el-menu-item index="Json2xml">XML转换</el-menu-item>
                <el-menu-item index="Thematic">专题地图</el-menu-item>
              </el-menu>
            </div>
          </el-col>
        </el-row>

      </el-header>
      <el-main type="flex" justify="center" align="middle">
          <router-view></router-view>
      </el-main>
      <el-footer type="flex" justify="center" align="middle">
        <div class="text-sm text-light-900">
          © 2022 DDAKUN with Hayasaka
        </div>
      </el-footer>
    </el-container>
  </div>
</template>

<script>
export default {
  name: 'App',
  components: {

  }
}
</script>

<style scoped>
.el-header {
  padding: 0;
}

.el-main{
  height: 89.5vh;
  padding: 0;
}

.el-footer{
  height: 2vh !important;
  padding: 0;
}
</style>
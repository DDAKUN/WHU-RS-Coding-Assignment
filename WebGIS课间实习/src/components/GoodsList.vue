<template>
  <div class="index-container" >
    <ul>
      <li v-for="item in fruitList" :key="item.id">

        <img :src="item.url" alt>
        <p>商品名:{{ item.name }}</p>
        <p>¥:{{ item.price }}</p>
        <el-button @click="add2Cart(item); open2();" style="margin-top:10px;" type="primary">加入购物车</el-button>
      </li>
    </ul>
  </div>
</template>
<script>
import { mapMutations, mapActions } from 'vuex'
export default {
  data() {
    return {
      fruitList: [
        {
          id: 10001,
          num: 1,
          url:
            "/img/北京.jpeg",
          name: "北京地理信息",
          price: 15
        },
        {
          id: 10002,
          num: 1,
          url:
            "/img/武汉.jpeg",
          name: "武汉遥感图像",
          price: 3.5
        },
        {
          id: 10003,
          num: 1,
          url:
            "/img/重庆.jpeg",
          name: "重庆遥感图像",
          price: 20
        },
        {
          id: 10004,
          num: 1,
          url:
            "/img/上海.jpeg",
          name: "上海地图",
          price: 35
        }
      ]
    };
  },
  // 方法
  methods: {
    ...mapMutations({
      add2Cart: 'addGoods'
    }),
    open2() {
      this.$message({
        showClose: true,
        message: '已成功加入购物车',
        type: 'success'
      });
    },
    // ...mapActions({
    //   add2Cart:'asyncAddGoods'
    // })
    /**
    add2Cart(friut) {
      // 假设每次添加的时候，数量都是1
      friut.num = 1

      // 调用vuex中的mutations
      this.$store.commit('addGoods',JSON.parse(JSON.stringify(friut)))
      // this.$store.commit('addGoods',friut)

      // 调用vuex中的actions
      // this.$store.dispatch('asyncAddGoods',JSON.parse(JSON.stringify(friut)))
    }
     */
    //  ...mapMutations({
    //   add2Cart: 'addGoods' // 将 `this.add()` 映射为 `this.$store.commit('increment')`
    // })
  }
};
</script>
<style >
.index-container ul {
  display: flex;
  @apply items-center justify-center
}

.index-container ul li {
  width: 200px;
  height: 300px;
  border: 1px solid #000;
  margin: 10px;
  text-align: center;
}

.index-container ul li a {
  display: block;
}

.index-container ul li a p {
  background-color: #0094ff;
  color: white;
  padding-left: 20px;
}

.index-container ul li img {
  width: 180px;
  height: 180px;
  display: block;
  margin: 10px auto 0;
}
</style>

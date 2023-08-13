import Vue from 'vue'
import App from './App.vue'
import router from "./router";
import ElementUI from 'element-ui';
import 'element-ui/lib/theme-chalk/index.css';
import 'windi.css'
import * as echarts from "echarts";
import myStore from './store/'



Vue.prototype.$echarts = echarts;
Vue.use(ElementUI);
Vue.config.productionTip = false

new Vue({
  router,
  store:myStore,
  render: h => h(App),
}).$mount('#app')

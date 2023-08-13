import Vue from "vue";
import VueRouter from "vue-router";
import Home from '../components/Home.vue'
import Map from '../components/Map.vue'
import ShoppingCart from '../components/ShoppingCart.vue'
import Good from '../components/GoodsList.vue'
import China from '../components/China.vue'
import Json from '../components/json2xml.vue'
import Thematic from '../components/Thematic.vue'
Vue.use(VueRouter);

const routes = [
  {
    path: "/",
    name: "Home",
    component: Home,
  },
  {
    path: "/Map",
    name: "Map",
    component: Map,
  },
  {
    path: "/Shoppingcart",
    name: "Shoppingcart",
    component: ShoppingCart,
  },
  {
    path: "/Goods",
    name: "Goods",
    component: Good,
  },
  {
    path: "/China",
    name: "China",
    component: China,
  },  
  {
    path: "/Json2xml",
    name: "Json2xml",
    component: Json,
  },
  {
    path: "/Thematic",
    name: "Thematic",
    component: Thematic,
  },
];

const router = new VueRouter({
  routes,
});


export default router;
import Vue from 'vue'
import Vuex from 'vuex'
Vue.use(Vuex) //Vue.propertype.$store = xxx

const moduleA = {
    // 状态就是数据
    state:{
        goodsList:JSON.parse(localStorage.getItem('cartList') || '[]') // 商品列表，刚开始为空
    },
    // Vuex中的getters 和Vue中filter、computed都是需要返回值
    getters:{
        /**
         * 这里面的参数必须是state
         * 
         * 第一次使用的会执行
         * 后面当我们 getTotalCount 中 使用/依赖的数据发生了变化
         */
        getTotalCount(state){
            console.log("----------------------")
            let totalCount = 0
            state.goodsList.forEach(item=>{
                totalCount += item.num
            })

            return totalCount
        },
        getGoodsList(state){
            return state.goodsList
        }
    },
    //mutations
    mutations:{
        /**
         * state 就是固定写法，它代表的就是上面state对象
         * 
         * 参数1：state对象，这个必须放在第一个位置
         * 参数2：载荷
         * 
         * 
         * 这个地方需要处理一下，如果添加的商品 state.goodsList 存在
         * 就在之前的那个对象上把数量加起来
         * 
         * 如果没有，再push条新的
         */
        addGoods(state,goods){
            // oldGoods，就是第一次添加进去的那个对象
            const oldGoods = state.goodsList.find(item=>item.id === goods.id)
            
            if (oldGoods) { //找到了，之前存在过
                 oldGoods.num += goods.num
            } else { // 没找到，直接新增
                state.goodsList.push(goods)
            }
            //ES6 如何从对象中，找到某个元素
            // console.log(state.goodsList)
        }
    },
    actions:{
        /**
        asyncAddGoods(context,goods){
            // 模拟耗时间操作
            setTimeout(() => {
                context.commit('addGoods',goods)
            }, 3000);
        }
         */
        asyncAddGoods({commit},goods){
            // 模拟耗时间操作
            setTimeout(() => {
                commit('addGoods',goods)
            }, 1000);
        }
    }
}

const orderModule = {
    state:{
        orderList:[]
    }
}

// 使用了module
/** 
const store = new Vuex.Store({
    modules:{
        cart:moduleA,
        order:orderModule
    }
})
*/

// 没有使用module
const store = new Vuex.Store({
    // 状态就是数据
    state:{
        goodsList:JSON.parse(localStorage.getItem('cartList') || '[]'), // 商品列表，刚开始为空
    },
    // Vuex中的getters 和Vue中filter、computed都是需要返回值
    getters:{
        /**
         * 这里面的参数必须是state
         * 
         * 第一次使用的会执行
         * 后面当我们 getTotalCount 中 使用/依赖的数据发生了变化
         */
        getTotalCount(state){
            console.log("----------------------")
            let totalCount = 0
            state.goodsList.forEach(item=>{
                totalCount += item.num
            })

            return totalCount
        },
        getGoodsList(state){
            return state.goodsList
        }
    },
    //mutations
    mutations:{
        /**
         * state 就是固定写法，它代表的就是上面state对象
         * 
         * 参数1：state对象，这个必须放在第一个位置
         * 参数2：载荷
         * 
         * 
         * 这个地方需要处理一下，如果添加的商品 state.goodsList 存在
         * 就在之前的那个对象上把数量加起来
         * 
         * 如果没有，再push条新的
         */
        addGoods(state,goods){
            // oldGoods，就是第一次添加进去的那个对象
            const oldGoods = state.goodsList.find(item=>item.id === goods.id)
            
            if (oldGoods) { //找到了，之前存在过
                 oldGoods.num += goods.num
            } else { // 没找到，直接新增
                state.goodsList.push(goods)
            }
            //ES6 如何从对象中，找到某个元素
            // console.log(state.goodsList)
        }
    },
    actions:{
        asyncAddGoods(context,goods){
            // console.log(context)
            // 模拟耗时间操作
            setTimeout(() => {
                context.commit('addGoods',goods)
            }, 1000);
        }
        /*
        asyncAddGoods({commit},goods){
            // console.log(goods)
            // 模拟耗时间操作
            setTimeout(() => {
                // 在这个调用之前需要做耗时间操作的时候
                commit('addGoods',goods)
            }, 3000);
        }
        */
    }
})

window.onbeforeunload = function(){
    // 保存到本地
    window.localStorage.setItem('cartList',JSON.stringify(store.getters.getGoodsList))
}

export default store
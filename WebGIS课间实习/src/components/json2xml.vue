<template>
<div class="row" >
    <el-row class="buttons">
        <el-button id="submitBTN" @click="beautify();">格式化</el-button>
        <el-button type="primary" id="submitBTN2" @click="minify();">压缩</el-button>
        <el-button type="success" @click="submitBTN3()">验证</el-button>
        <el-button type="info" @click ="jsonToxml();">JSON 转 XML</el-button>
        <el-button type="warning" @click ="jsonTocsv();">JSON 转 CSV</el-button>
        <el-button type="danger" @click ="xmlTocsv();">XML 转 CSV</el-button>
    </el-row>
    <el-divider></el-divider>
    <div class="editor">
        <div class="editor1">
            <div id="jsoneditor1"  style="height: 500px; width: 100%;">
                <vue-json-editor                         
                    v-model="json" 
                    style="height: 100%;"
                    :show-btns="false" 
                    :mode="'code'" 
                    :exapndedOnStart="true" 
                    lang="zh"  
                    ></vue-json-editor>
            </div>
        </div>
        <div class="transt">
            <el-button type="primary" icon="el-icon-arrow-right" @click="jsonToxml()" id="right"></el-button>
            <p></p>
            <el-button type="primary" icon="el-icon-arrow-left" @click="xml2json()" id="left"></el-button>
        </div>
        <div class="editor2">
            <div id="jsoneditor2" style="height: 500px; width: 100%;">
                <vue-json-editor                         
                    v-model="jsontext2" 
                    style="height: 100%;"
                    :show-btns="false" 
                    :mode="'text'" 
                    :exapndedOnStart="true" 
                    lang="zh"  
                    ></vue-json-editor>
            </div>
        </div>
    </div>
</div>
    
</template>
<script>

import vueJsonEditor from 'vue-json-editor'
import vkbeautify from 'vkbeautify'
const x2js = require('x2js');
export default {
    data(){
        return {
            jsontext1:"",
            jsontext2:"",
            json: {"学生":{"信息":[{"id":"2017302590041","name":"熊淑萍","性别":"女"},{"id":"2017302590207","name":"谢一涵","性别":"女"},{"id":"2017302590232","name":"马洁","性别":"女"}]}}

        }
    },
    methods:{
        beautify() {
            var content = this.json;
            if (content.length == 0) {
                return false;
            }
            try {
                console.log('格式化');

                var jsonStr = this.json;
                this.json = JSON.parse(jsonStr);
                
            } catch (e) {
                $("#warning").html("<div class=\"alert alert-danger\">JSON 数据错误："+e+"</div>").show().delay(5000).fadeOut();
            }
        },
        minify() {
                var jsonStr = this.json;
                this.json=JSON.stringify(this.json, null, 0);

        },
        jsonToxml(){
            var x2jsone = new x2js();
            var xmlAsStr = x2jsone.js2xml( this.json );
            this.jsontext2=xmlAsStr;
        },
        xml2json(){
            var x2jsone = new x2js()
            var jsonObj = x2jsone.xml2js(this.jsontext2);
            this.json=jsonObj;

        },
        jsonTocsv(){
            var type1 = typeof this.json;
            var csvdata=this.json;
            while(type1=='object'){
                var key=Object.keys(csvdata);
                if(key.length>1){
                    break;
                }
                else{
                    type1= typeof csvdata[key[0]];
                    csvdata=csvdata[key[0]];
                }
            };
            var key=Object.keys(csvdata[0]);
            var header="";
            var content="";
            key.forEach(item=>{
                header += item + ",";
            });
            header = header.substring(0, header.length - 1);
            csvdata.forEach(item=>{
                key.forEach(value=>{
                content+=item[value]+",";
            });
            content = content.substring(0, content.length - 1);
            content+='\n';
            });
            this.jsontext2=header+'\n'+content;
        },
        jsonTocsvbyjson(data) {

            var arr = [];
            var flag = true;

            var header = "";
            var content = "";
            var headFlag = true;
            try {

                var type1 = typeof data;
                if (type1 != "object") {
                    data = this.processJSON($.parseJSON(data));
                } else {
                    data = this.processJSON(data);
                    console.log(data);

                }

            } catch (e) {
               
                return false;
            }

            $.each(data, function(k, value) {
                if (k % 2 == 0) {
                    if (headFlag) {
                        if (value != "end") {
                            header += value + ",";
                        } else {
                            // remove last colon from string
                            header = header.substring(0, header.length - 1);
                            headFlag = false;
                        }
                    }
                } else {
                    if (value != "end") {
                        var temp = data[k - 1];
                        if (header.search(temp) != -1) {
                            content += value + ",";
                        }
                    } else {
                        // remove last colon from string
                        content = content.substring(0, content.length - 1);
                        content += "\n";
                    }
                }

            });

            return (header + "\n" + content);
        },
        xmlTocsv(){
            var x2jsone = new x2js()
            var jsondata=x2jsone.xml2js(this.jsontext2);
            var type1 = typeof jsondata;
            var csvdata=jsondata;
            while(type1=='object'){
                var key=Object.keys(csvdata);
                if(key.length>1){
                    break;
                }
                else{
                    type1= typeof csvdata[key[0]];
                    csvdata=csvdata[key[0]];
                }
            };
            var key=Object.keys(csvdata[0]);
            var header="";
            var content="";
            key.forEach(item=>{
                header += item + ",";
            });
            header = header.substring(0, header.length - 1);
            csvdata.forEach(item=>{
                key.forEach(value=>{
                content+=item[value]+",";
            });
            content = content.substring(0, content.length - 1);
            content+='\n';
            });
            this.jsontext2=header+'\n'+content;
        }
    },
     components: {
      vueJsonEditor
    },

    created(){
			this.$store.dispatch('changeShow','json2xml');

    }
}
</script>
<style scoped>
.row{
    box-shadow: 0 2px 4px rgba(0, 0, 0, .12), 0 0 6px rgba(0, 0, 0, .04);
    width: 1200px;
    margin-left:250px;
    position: relative;
    height: 650px;
}
.buttons{
    padding-top: 10px;
    padding-left: 20px;
    color: #F5F5F5;
}
.editor1{
    width:500px;
    float: left;
    padding-top: 10px;
    padding-left: 30px;
    float: top;
    position: absolute;

}
.editor2{
    width:500px;
    float: right;
    float: top;
    padding-top: 10px;
    padding-right: 30px;
    white-space:pre;
}
.transt{
    padding-left: 570px;
    padding-top: 20px;
    float: left;
}
#right{
    float: left;
    margin-bottom: 10px;
}
#left{
    float: left;
    margin-bottom: 10px;
}
.jsoneditor2{
    white-space:pre;

}
</style>
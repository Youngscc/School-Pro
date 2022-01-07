//index.js
//获取应用实例
const app = getApp()

Page({
  
  data: {
    PageCur: 'home',
    name:null,
    identity:0
 
  },

 
  
  NavChange(e) {
    
    this.setData({
      PageCur: e.currentTarget.dataset.cur,
      name:app.globalData.userid,
      identity:app.globalData.identity
    })
  },
  //事件处理函数  
  
  
})


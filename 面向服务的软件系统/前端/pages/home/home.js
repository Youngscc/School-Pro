// pages/home/home.js
const app = getApp()
Page({
  options: {
    addGlobalClass: true,
  },
  /**
   * 页面的初始数据
   */
  data: {
    StatusBar: app.globalData.StatusBar,
    CustomBar: app.globalData.CustomBar,
    motto: 'Hi 开发者!',
    userInfo: {},
    hasUserInfo: false,
    canIUse: wx.canIUse('button.open-type.getUserInfo'),
    
    var:[{
      title: '查看附近设备情况',
      name: 'layout',
      color: 'cyan',
      icon: 'newsfill'
    },
    {
      title: '我要换奖品',
      name: 'background',
      color: 'blue',
      icon: 'colorlens'
    }
  ],
    
    
    elements: [{
      title: '查看附近设备情况',
      name: 'seek',
      color: 'cyan',
      icon: 'newsfill'
    }
  ],
  },

  /**
   * 生命周期函数--监听页面加载
   */
  bindViewTap: function() {
    wx.navigateTo({
      url: '../login/login'
    })
  },

  

  onLoad: function () {
    
    if (app.globalData.userInfo) {
      this.setData({
        userInfo: app.globalData.userInfo,
        hasUserInfo: true
      })
    } else if (this.data.canIUse){
      // 由于 getUserInfo 是网络请求，可能会在 Page.onLoad 之后才返回
      // 所以此处加入 callback 以防止这种情况
      app.userInfoReadyCallback = res => {
        this.setData({
          userInfo: res.userInfo,
          hasUserInfo: true
        })
      }
    } else {
      // 在没有 open-type=getUserInfo 版本的兼容处理
      wx.getUserInfo({
        success: res => {
          app.globalData.userInfo = res.userInfo
          this.setData({
            userInfo: res.userInfo,
            hasUserInfo: true
          })
        }
      })
      
    }
    this.setData({
      elements:this.data.var


    })
  },
  getUserInfo: function(e) {
    console.log(e)
    app.globalData.userInfo = e.detail.userInfo
    this.setData({
      userInfo: e.detail.userInfo,
      hasUserInfo: true
    })
  }
  

  

  
})
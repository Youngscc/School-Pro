// pages/admin/admin.js
const app=getApp()
Page({

  /**
   * 页面的初始数据
   */
  data: {
    username:null,

    elements: [{
      title: '用户管理',
      name: 'userManage',
      color: 'cyan',
    },
    {
      title: '设备管理',
      name: 'eqManage',
      color: 'blue',
    },
    {
      title: '查看事件',
      name: 'examine',
      color: 'green',
    },
  ]
  },

  onClick: function(e)
  {
    app.globalData.userid=null;
    app.globalData.identity=null;
    wx.navigateTo({
      url:'../index/index'
    })
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    this.setData({
      username:app.globalData.username
    })
  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {

  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function () {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function () {

  }
})
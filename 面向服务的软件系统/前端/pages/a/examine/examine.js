// pages/a/examine/examine.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    picker:['查看报修记录','查看维修记录'],
    index:null,
    id:null
  },

  PickerChange(e) {
    this.setData({
      index: e.detail.value
      
    })
  },

  inputId:function(e) {
    this.setData({
      id:e.detail.value
    })

  },

  onClick1:function(){
    if(this.data.id!=null && this.data.id!='')
    {
      wx.navigateTo({
        url: '../event1/event1?id='+this.data.id,
      })
    }
  },
  onClick2:function(){
    if(this.data.id!=null && this.data.id!='')
    {
      wx.navigateTo({
        url: '../event2/event2?id='+this.data.id,
      })
    }
    
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {

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
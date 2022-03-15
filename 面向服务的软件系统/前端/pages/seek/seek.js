// pages/seek/seek.js
const app = getApp()
Page({

  /**
   * 页面的初始数据
   */
  data: {
    ids:null,
    categorys:null,
    states:null,
    item:null
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    var item=[];
    var that=this;
    wx.request({
      url:'http://st.free.idcfengye.com/getEquipmentIDList', //服务器地址
  
  menthod: "GET",   
  header: {
    'content-type': 'application/json'
  },
  data: {
    
  },
  
  
  success:function (res) {
    
    console.log(".....回调函数....." );
    var Data=res.data;
    console.log(Data);
    
    that.setData({
      item:Data
    })
    console.log(that.data.item);
    

  
  

  
  
    
    
  }

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
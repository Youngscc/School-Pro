// pages/login/login.js
const app = getApp()
Page({

  /**
   * 页面的初始数据
   */
  data: {
    user:null,
    pass:null
  },


onClick:function() {
  console.log(this.data.user);
  wx.request({
    url:'http://st.free.idcfengye.com/login', //服务器地址

menthod: "GET",   
header: {
  'content-type': 'application/json'
},
data: {
  'username':this.data.user,
  'password':this.data.pass
},


success:function (res) {
  
  console.log(".....回调函数....." +res.data.u_id )
  var resData=res.data;
  if(resData.u_name!=undefined){
    app.globalData.identity=resData.identity;
    app.globalData.userid=resData.u_id;
    app.globalData.username=resData.u_name;
      wx:wx.showToast({
        title: '登录成功',
        duration: 2000,
      })
      wx.navigateTo({
        url: '../index/index',
      })
      
  }else{
    wx:wx.showToast({
      title: '登录失败',
      duration: 2000,
    })
  }

}  
})

},

username:function(e) {
  this.setData({
    user:e.detail.value
  })
},

password:function(e) {
  this.setData({
    pass:e.detail.value
  })
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
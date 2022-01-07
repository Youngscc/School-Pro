// pages/submit/submit.js
const app = getApp()
Page({

  /**
   * 页面的初始数据
   */
  data: {
    msgall:null,
    picker:null,
    index:null,
    msg:null
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    var that=this;
    wx.request({
      url:'http://st.free.idcfengye.com/stu/getCategoryList', //服务器地址
  
      menthod: "GET",   
      header: {
        'content-type': 'application/json'
      },
      data: {
   
      },
  
  
  success:function (res) {
    
    console.log(".....回调函数....." );
    var resData=res.data;
    
    var msg=[];
    for(var i=0;i<resData.length;i++)
    {
      msg[i]=resData[i].text;
      console.log(msg[i]);
    }
    that.setData({
      msgall:msg
    })
    var p=[];
    for(var i=0;i<resData.length;i++)
    {
      p[i]=resData[i].c_name;
      console.log(p[i]);
    }
    that.setData({
      picker:p
    })
    console.log(that.data.picker);
    console.log(that.data.msgall);
  
  }  
  })
  

  },
  PickerChange(e) {
    var that=this;

    console.log('123'+that.data.msgall[1]);
    this.setData({
      index: e.detail.value
      
    })

    
  },

  onClick: function () {
    wx.navigateTo({
      url: '../contact/contact'
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
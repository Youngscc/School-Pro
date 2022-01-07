// pages/a/userManage/userManage.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    picker:['添加用户','删除用户'],
    index:null,
    user:null,
    pass:null,
    picker2:['普通用户','维修人员','管理员'],
    index2:null,
    identity:null
  },

  PickerChange(e) {
    this.setData({
      index: e.detail.value
      
    })
  },

  PickerChange2(e) {
    this.setData({
      index2: e.detail.value
    })
  },

  onClickAdd: function () {
    var that=this;
    var iden=parseInt(that.data.index2)+1;
    console.log(iden)
    if(that.data.user!='' && that.data.user!=null && that.data.index2!=null)
    {
      wx.request({
        url:'http://st.free.idcfengye.com/administer/addUser', //服务器地址
    
    menthod: "GET",   
    header: {
      'content-type': 'application/json'
    },
    data: {
      'userName':that.data.user,
      'password':that.data.pass,
      'identity':iden
    },
    
    
    success:function (res) {
      
      console.log(".....回调函数....." +res.data.boolean );
      var resData=res.data;
      if(resData.boolean==true){
          wx.showToast({
            title: '成功',
            duration: 2000,
          })
          wx.navigateBack({
            delta: 1,
          })
          
      }else{
        wx.showToast({
          title: '失败',
          duration: 2000,
        })
      }
    
    }  
    })
    }
  },

  onClickDel:function() {
    console.log(this.data.user)
    var that=this;
    if(that.data.user!='' && that.data.user!=null && that.data.index!=null)
    {
      wx.request({
        url:'http://st.free.idcfengye.com/administer/removeUser', //服务器地址
    
    menthod: "GET",   
    header: {
      'content-type': 'application/json'
    },
    data: {
      'userName':that.data.user
    },
    
    
    success:function (res) {
      
      console.log(".....回调函数....." +res.data.boolean );
      var resData=res.data;
      if(resData.boolean==true){
          wx.showToast({
            title: '成功',
            duration: 2000,
          })
          wx.navigateBack({
            delta: 1,
          })
          
      }else{
        wx.showToast({
          title: '失败',
          duration: 2000,
        })
      }
    
    }  
    })
    }
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
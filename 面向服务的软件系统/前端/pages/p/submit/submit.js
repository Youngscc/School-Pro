// pages/p/submit/submit.js
const app=getApp()
Page({

  /**
   * 页面的初始数据
   */
  data: {
    picker:null,
    index:null,
    index2:null,
    picker2:null,
    input:null
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    var that=this;
    wx.request({
      url:'http://st.free.idcfengye.com/pro/getCategoryList', //服务器地址
  
      menthod: "GET",   
      header: {
        'content-type': 'application/json'
      },
      data: {
   
      },
  
  
  success:function (res) {
    
    var resData=res.data;
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
  
  }  
  })


  },

  PickerChange(e) {
    var that=this;

    this.setData({
      index: e.detail.value
      
    })
    console.log('111'+that.data.picker[that.data.index]);
    wx.request({
      url:'http://st.free.idcfengye.com/pro/getEquipmentList', //服务器地址
  
      menthod: "GET",   
      header: {
        'content-type': 'application/json'
      },
      data: {
        'categoryName': that.data.picker[that.data.index]
      },
  
  
  success:function (res) {
    
    var resData=res.data;
    var p=[];
    for(var i=0;i<resData.length;i++)
    {
      p[i]=resData[i].e_id;
      console.log(p[i]);
    }
    that.setData({
      picker2:p
    })
    console.log(that.data.picker);
  
  }  
  })
    
  },

  input:function(e) {
    this.setData({
      input:e.detail.value
    })
  },

  onClick:function() {
    
    var that=this;
    console.log('eventid:'+that.data.picker2[that.data.index2])
    if(that.data.input==null || that.data.index==null || that.data.index2==null)
    {
      wx.showToast({
        title: '信息不足',
        duration: 1000
      })
    }
    else
    {
      wx.request({
        url:'http://st.free.idcfengye.com/pro/maintain', //服务器地址
    
        menthod: "GET",   
        header: {
          'content-type': 'application/json'
        },
        data: {
          'userID': app.globalData.userid,
          'equipmentID': that.data.picker2[that.data.index2],
          'text': that.data.input
        },
    
    
    success:function (res) {
      
      var resData=res.data;
      console.log(resData);
      if(resData.boolean==true)
      {
        wx.navigateBack({
          delta: 1,
        })
      }
      else
      {
        wx.showToast({
          title: '该设备无需修复',
        })
      }
    
    }  
    })
    }
  },

  PickerChange2(e) {

    this.setData({
      index2: e.detail.value
      
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
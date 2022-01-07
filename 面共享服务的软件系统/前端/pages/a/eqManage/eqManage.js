// pages/a/eqManage/eqManage.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    picker:['添加设备种类','添加设备个体','删除设备个体'],
    index:null,
    cate:null,
    text:null,
    del:null
  },

  PickerChange(e) {
    this.setData({
      index: e.detail.value
      
    })
  },

  addCate:function(e) {
    this.setData({
      cate:e.detail.value
    })

  },

  addText:function(e) {
    this.setData({
      text:e.detail.value
    })

  },

  inputDelete:function(e) {
    this.setData({
      del:e.detail.value
    })

  },

  onClickAddCate:function(e) {
    var that=this;
    if(this.data.cate!=null && this.data.cate!='')
    {
      wx.request({
        url:'http://st.free.idcfengye.com/administer/addCategory', //服务器地址
    
    menthod: "GET",   
    header: {
      'content-type': 'application/json'
    },
    data: {
      'categoryName':that.data.cate
    },
    
    
    success:function (res) {
      
      var resData=res.data;
      console.log(resData);
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
          title: '命名重复',
          duration: 2000,
        })
      }
    
    }  
    })
    }

  },

  onClickAddOne:function(e) {
    var that=this;
    if(this.data.cate!=null && this.data.text!=null && this.data.cate!='' && this.data.text!='')
    {
      wx.request({
        url:'http://st.free.idcfengye.com/administer/addEquipment', //服务器地址
    
    menthod: "GET",   
    header: {
      'content-type': 'application/json'
    },
    data: {
      'categoryName':that.data.cate,
      'text':that.data.text
    },
    
    
    success:function (res) {
      
      var resData=res.data;
      console.log(resData);
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

  onClickDelete:function(e) {
    var that=this;
    console.log(that.data.del)
    if(this.data.del!=null && this.data.del!='')
    {
      wx.request({
        url:'http://st.free.idcfengye.com/administer/removeEquipment', //服务器地址
    
    menthod: "GET",   
    header: {
      'content-type': 'application/json'
    },
    data: {
      'equipmentID':that.data.del
    },
    
    
    success:function (res) {
      
      var resData=res.data;
      console.log(resData);
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
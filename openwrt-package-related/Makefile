
include $(TOPDIR)/rules.mk

PKG_NAME:=lib-lua-syslog
PKG_VERSION:=1
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

# 有什麼需要的 flag 可以帶在這邊
TARGET_CFLAGS  += -Wall -Werror -D_GNU_SOURCE -I$(STAGING_DIR)/usr/include
TARGET_LDFLAGS += -llua -lm -ldl
# TARGET_CXXFLAGS+=
# TARGET_CPPFLAGS+=

include $(INCLUDE_DIR)/package.mk

# 用到 CMake 才要
include $(INCLUDE_DIR)/cmake.mk
CMAKE_OPTIONS+=
CMAKE_HOST_OPTIONS+=

# kernel module 才要
# include $(INCLUDE_DIR)/kernel.mk

define Package/$(PKG_NAME)
	SUBMENU:=Libs
	CATEGORY:=Arcadyan
	TITLE:=Syslog library for lua binding
	DEPENDS:=+lua
endef

# menuconfig 利用搜尋功能找出package後，下面比較長的那段敘述
define Package/$(PKG_NAME)/description
	Syslog library for lua binding
endef

# 通常是這個 package 需要使用 autoconf / automake 的時候才需要
# define Build/Configure
# endef

# 下載網路上的 source code tar 檔
# 或是用 svn / git 去抓回來的話，應該是不需要的
# 但如果是你自己寫 source code 的話
# 這邊通常要把 source code copy 到 build 路徑$(PKG_BUILD_DIR)去
define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(call Build/Prepare/Default)
	$(CP) -rf ./codes/* $(PKG_BUILD_DIR)/
endef

# 如果不特別定義的話，就會 call 到裡面那層的 makefile 去
# 如果在一個 package 裡面只要編一個 app / 一個 lib
# 這個通常不必設定
# 但如果一個 package 裡面會編出多個 app / app + lib 混合
# 這邊就要改了
# define Build/Compile
# endef

# 一般來說，install 的動作可以擺在 src/Makefile 裡面做就好了？
# 但如果你還想 copy files/ 裡面的東西到 /etc/init.d？
# 或是 copy 到 /etc/config/ ，那可以在這裡做
define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib/lua
	$(CP) $(PKG_BUILD_DIR)/libluasyslog.so $(1)/usr/lib/lua/syslog.so
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/lib/lua
	$(CP) $(PKG_BUILD_DIR)/libluasyslog.so $(1)/usr/lib/lua/syslog.so
endef

$(eval $(call BuildPackage,$(PKG_NAME)))

# Copyright (C) 2019 Onion Corporation
#
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
PKG_NAME:=littlev-demo
PKG_VERSION:=0.0.1
PKG_RELEASE:=1


PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk


# application package
define Package/littlev-demo
	SECTION:=onion
	CATEGORY:=Onion
	SUBMENU:=Utilities
	TITLE:=LittleV GL framework test binary
endef

define Package/littlev-demo/description
LittleV GL framework test
endef


# TARGET_CFLAGS += -I$(STAGING_DIR)/usr/include
# TARGET_LDFLAGS += -L$(STAGING_DIR)/usr/lib

# define Build/Compile
# 	$(MAKE) -C $(PKG_BUILD_DIR)/ \
# 	CC="$(TARGET_CC)" \
# 	CFLAGS="$(TARGET_CFLAGS)" \
# 	LDFLAGS="$(TARGET_LDFLAGS)"
# endef

define Package/littlev-demo/install
	$(INSTALL_DIR) $(1)/usr/bin
	# install the binary
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bin/demo $(1)/usr/bin/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
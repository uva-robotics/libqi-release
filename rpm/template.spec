Name:           ros-indigo-naoqi-libqi
Version:        2.5.0
Release:        1%{?dist}
Summary:        ROS naoqi_libqi package

Group:          Development/Libraries
License:        BSD
URL:            http://doc.aldebaran.com/libqi
Source0:        %{name}-%{version}.tar.gz

Requires:       boost-devel
BuildRequires:  boost-devel
BuildRequires:  ros-indigo-catkin

%description
Aldebaran's libqi: a core library for NAOqiOS development

%prep
%setup -q

%build
# In case we're installing to a non-standard location, look for a setup.sh
# in the install tree that was dropped by catkin, and source it.  It will
# set things like CMAKE_PREFIX_PATH, PKG_CONFIG_PATH, and PYTHONPATH.
if [ -f "/opt/ros/indigo/setup.sh" ]; then . "/opt/ros/indigo/setup.sh"; fi
mkdir -p obj-%{_target_platform} && cd obj-%{_target_platform}
%cmake .. \
        -UINCLUDE_INSTALL_DIR \
        -ULIB_INSTALL_DIR \
        -USYSCONF_INSTALL_DIR \
        -USHARE_INSTALL_PREFIX \
        -ULIB_SUFFIX \
        -DCMAKE_INSTALL_LIBDIR="lib" \
        -DCMAKE_INSTALL_PREFIX="/opt/ros/indigo" \
        -DCMAKE_PREFIX_PATH="/opt/ros/indigo" \
        -DSETUPTOOLS_DEB_LAYOUT=OFF \
        -DCATKIN_BUILD_BINARY_PACKAGE="1" \

make %{?_smp_mflags}

%install
# In case we're installing to a non-standard location, look for a setup.sh
# in the install tree that was dropped by catkin, and source it.  It will
# set things like CMAKE_PREFIX_PATH, PKG_CONFIG_PATH, and PYTHONPATH.
if [ -f "/opt/ros/indigo/setup.sh" ]; then . "/opt/ros/indigo/setup.sh"; fi
cd obj-%{_target_platform}
make %{?_smp_mflags} install DESTDIR=%{buildroot}

%files
/opt/ros/indigo

%changelog
* Sun Mar 13 2016 Mikael Arguedas <mikael.arguedas@gmail.com> - 2.5.0-1
- Autogenerated by Bloom

* Sun Mar 13 2016 Mikael Arguedas <mikael.arguedas@gmail.com> - 2.5.0-0
- Autogenerated by Bloom

* Tue May 19 2015 Mikael Arguedas <mikael.arguedas@gmail.com> - 2.3.0-2
- Autogenerated by Bloom

* Wed May 13 2015 Mikael Arguedas <mikael.arguedas@gmail.com> - 2.3.0-1
- Autogenerated by Bloom

* Wed May 13 2015 Mikael Arguedas <mikael.arguedas@gmail.com> - 2.3.0-0
- Autogenerated by Bloom


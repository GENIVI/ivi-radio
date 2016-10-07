cd doc
cd doc-doxy
rm -R html
rm -R latex
cd ..
cd ..
doxygen doxy_conf
cd doc
cd doc-doxy
cd html
gnome-open index.html

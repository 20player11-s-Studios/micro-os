#ifndef PKG_H
#define PKG_H

void pkg_init(void);
void pkg_install(const char* name);
void pkg_remove(const char* name);
void pkg_update(void);
void pkg_search(const char* name);

#endif

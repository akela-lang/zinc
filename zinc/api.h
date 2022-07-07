#ifndef _API_H
#define _API_H

#ifdef EXPORT
#define ZINC_API __declspec(dllexport)
#else
#define ZINC_API __declspec(dllimport)
#endif

#endif

#pragma once

#define DISABLE_ASSIGN_AND_COPY(klass)    \
  klass(const klass&) = delete;           \
  klass(klass&&) = delete;                \
  klass operator=(const klass&) = delete; \
  klass operator=(klass&&) = delete

#!/bin/bash

GIT_HOOK_PATH=".git/hooks"
CUSTOM_HOOK_PATH=$(realpath ./git-hooks)

if [ -d $GIT_HOOK_PATH ]; then
  echo "Deleting original git hooks directory ($GIT_HOOK_PATH)"
  rm -r $GIT_HOOK_PATH
fi

if [[ -L "$GIT_HOOK_PATH" ]]; then
  echo "$CUSTOM_HOOK_PATH already linked to $GIT_HOOK_PATH"
else
  echo "Linking $CUSTOM_HOOK_PATH to $GIT_HOOK_PATH"
  ln -s $CUSTOM_HOOK_PATH $GIT_HOOK_PATH
fi

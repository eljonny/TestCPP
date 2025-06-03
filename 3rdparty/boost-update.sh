#!/bin/bash

NEW_BOOST_VERSION="$1"
CURRENT_BOOST_COMMIT_SHA="$(git rev-parse HEAD)"

git checkout "boost-$NEW_BOOST_VERSION"
git cherry-pick "$CURRENT_BOOST_COMMIT_SHA"
git commit -am "Apply CMake changes to enable project usage as git submodule directly."
git tag -s "boost-$NEW_BOOST_VERSION-cmake-git-submodule" --file=../cmake-git-submodule.tag.msg
git push --tags

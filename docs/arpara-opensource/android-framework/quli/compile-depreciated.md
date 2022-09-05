
## compile

### fix: `missing dependencies`（有副作用）

using `ALLOW_MISSING_DEPENDENCIES=true` when compiling, ref: [March AOSP builds failing with undefined module "java_api_finder" [150626837] - Visible to Public - Issue Tracker](https://issuetracker.google.com/issues/150626837?enable_mat=true&pli=1)

用这个虽然可以忽略编译前期的 dependencies 缺失问题，但是后续还是会有编译无法通过的bug。

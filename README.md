# Setup SFML
- Download + unpack : https://sfml-dev.org/download.php
- Update File :
-- Zaxxon2020/Zaxxon2020.vcxproj --
Change value PATH_TO_SFLM_LIBRARY to the SFLM Location Path
```
line 102 : <AdditionalIncludeDirectories>PATH_TO_SFLM_LIBRARY\include;%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
...
line 107 : <AdditionalLibraryDirectories>PATH_TO_SFLM_LIBRARY\lib;%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>
...
line 135:  <AdditionalIncludeDirectories>PATH_TO_SFLM_LIBRARY\include;%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
...
line 142:  <AdditionalLibraryDirectories>PATH_TO_SFLM_LIBRARY\lib;%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>
```
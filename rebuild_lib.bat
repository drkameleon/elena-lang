bin\sg dat\sg\syntax.txt
move dat\sg\syntax.dat bin

bin\og dat\og\rules.txt
move dat\og\rules.dat bin

bin\asm2binx src32\core\core_routines.esm lib32\system
bin\asm2binx asm\x32\core.asm bin\x32
bin\asm2binx asm\x32\corex.asm bin\x32                
bin\asm2binx asm\x32\coreapi.asm bin\x32
bin\asm2binx asm\x32\core_vm.asm bin\x32
bin\asm2binx asm\x32\core_win.asm bin\x32

bin\asm2binx -amd64 asm\amd64\core.asm bin\amd64
bin\asm2binx -amd64 asm\amd64\core_win.asm bin\amd64
bin\asm2binx -amd64 asm\amd64\coreapi.asm bin\amd64

bin\elc src32\system\system.prj
bin\elc src32\extensions\extensions.prj
bin\elc src31\net\net.prj
bin\elc src32\forms\forms.prj
bin\elc src32\sqlite\sqlite.prj
bin\elc src32\cellular\cellular.prj
bin\elc src32\graphics\graphics.prj
bin\elc src32\xforms\xforms.prj

rem bin\elc src31\system\system_64.prj

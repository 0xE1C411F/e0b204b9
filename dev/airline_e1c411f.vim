" STANDARD
let s:S2 = [ '#EBE9E8' , '#1E2730' ,  7, 8]
let s:S3 = [ '#EBE9E8' , '#0A0F14' ,  7, 0]

" NORMAL
let s:NO = [ '#2F8FFF' , '#0A0F14' , 12, 0]

" INSERT
let s:IN = [ '#A847FE' , '#0A0F14' , 13, 0]

" VISUAL
let s:VI = [ '#FABE4B' , '#0A0F14' , 11, 0]

" REPLACE
let s:RE = [ '#FFFFFF' , '#C33027' , 15, 1]

" COMMAND
let s:CO = [ '#64C58C' , '#0A0F14' , 10, 0]

" INACTIVE
let s:IA = [ '#1E2730' , '#0A0F14' ,  8, 0]

let g:airline#themes#e1c411f#palette = {}
let g:airline#themes#e1c411f#palette.normal = airline#themes#generate_color_map(s:NO, s:S2, s:S3)
let g:airline#themes#e1c411f#palette.insert = airline#themes#generate_color_map(s:IN, s:S2, s:S3)
let g:airline#themes#e1c411f#palette.visual = airline#themes#generate_color_map(s:VI, s:S2, s:S3)
let g:airline#themes#e1c411f#palette.replace = airline#themes#generate_color_map(s:RE, s:S2, s:S3)
let g:airline#themes#e1c411f#palette.commandline = airline#themes#generate_color_map(s:CO, s:S2, s:S3)
let g:airline#themes#e1c411f#palette.inactive = airline#themes#generate_color_map(s:IA, s:IA, s:IA)


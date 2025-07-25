## 3.5 Structures N-R

----------
#### NameArrayAddFlags
    NameArrayAddFlags       record
        NAAF_SET_DATA_ON_REPLACE        :1
                                        :15
    NameArrayAddFlags       end

NAAF_SET_DATA_ON_REPLACE  
If replacing an existing name set, set data for the name to the data passed.

**Library:** chunkarr.def

----------
#### NameArrayElement
    NameArrayElement        struct
        NAE_meta        RefElementHeader    ;standard ElementArray header
        NAE_data        label byte          ;data
    NameArrayElement        ends

The name itself immediately follows the byte of data.

**Library:** chunkarr.def

----------
#### NameArrayHeader
    NameArrayHeader     struct
        NAH_meta            ElementArrayHeader
        NAH_dataSize        word
    NameArrayHeader     ends

This structure must be at the front of every name array. Since name arrays 
are special kinds of element arrays, the **NameArrayHeader** must itself 
begin with an **ElementArrayHeader**.

*NAH_meta* stores this element array header.

*NAH_dataSize* stores the size of the data section of each element in the name 
array.

**Library:** chunkarr.def

----------
#### NameArrayMaxElement
    NameArrayMaxElement         struct
        NAME_meta           RefElementHeader
        NAME_data           byte NAME_ARRAY_MAX_DATA_SIZE dup (?)
        NAME_name           char NAME_ARRAY_MAX_NAME_SIZE dup (?)
    NameArrayMaxElement         ends

**Library:** chunkarr.def

----------
#### NavigateCommonFlags
    NavigateCommonFlags         record
        NCF_IS_COMPOSITE            :1
        NCF_IS_FOCUSABLE            :1
        NCF_IS_MENU_RELATED         :1
        NCF_IS_ROOT_NODE            :1
                                    :4
    NavigateCommonFlags         end

NCF_IS_COMPOSITE  
Set this if calling from a composite object (is subclass of 
VisCompClass).

NCF_IS_FOCUSABLE  
Set this if specific UI will allow this object to get the focus. If 
NCF_IS_COMPOSITE is also set, means the object itself will get 
the focus first, followed by its children, in the navigation order.

NCF_IS_MENU_RELATED  
Set if this object is menu-related (menu button, or icon in 
header area).

NCF_IS_ROOT_NODE  
Set if this node is the root level of the tree. 

**Library:** Objects/visC.def

----------
#### NavigateCommonParams
    NavigateCommonParams            struct
        NCP_object              optr
        NCP_navFlags            NavigateFlags
        NCP_navCommonFlags      NavigateCommonFlags
        NCP_genericData         lptr
    NavigateCommonParams            ends

*NCP_object* stores the object that originated the message. When returned, 
this entry stores the final recipient of the message.

*NCP_genericData* stores the chunk handle of generic instance data for the 
calling object, or zero if not there is no generic data. (This is used for checking 
for navigation hints on the object.)

**Library:** Objects/visC.def

----------
#### NavigateFlags
    NavigateFlags       record
        ; reply flags
        NF_COMPLETED_CIRCUIT            :1
        NF_REACHED_ROOT                 :1
                                        :6
        ; command flags (MUST BE IN LOWER BYTE)
                                        :1  ;reserved for future use
                                            ;(lines up with VTF_IS_COMPOSITE)
                                        :1  ;reserved for future use (lines up with 
                                            ; GS_ENABLED and NCF_FOCUSABLE)
        NF_NAV_MENU_BAR                 :1
                                        :1  ;reserved for future use(lines up with 
                                            ;VTF_IS_WIN_GROUP and NCF_IS_ROOT)
        NF_INITIATE_QUERY               :1
        NF_SKIP_NODE                    :1
        NF_TRAVEL_CIRCUIT               :1
        NF_BACKTRACK_AFTER_TRAVELING    :1
    NavigateFlags       end

NF_COMPLETED_CIRCUIT  
This is set when this message is received at a node and the 
originating node (in ^**lcx:dx**) matches the recipient node, 
meaning we have travelled the entire circuit. Recursion ends at 
this point. This is useful for preventing infinite looping in cases 
where the circuit consists of 1 object, and is handy for error 
checking after objects have been added/removed from the 
WIN_GROUP.

NF_REACHED_ROOT  
This might be useful for error checking. Is set as this message 
is received by the root (WIN_GROUP object, and is passed on to 
the first child.

NF_NAV_MENU_BAR  
Set to navigate through items considered part or the menu bar 
area: menu buttons, icons in the header area, etc. Clear this 
flag to navigate through control-items in the window area. 

NF_INITIATE_QUERY  
When a MSG_SPEC_NAVIGATE_TO_NEXT_FIELD or 
MSG_SPEC_NAVIGATE_TO_NEXT_FIELD handler sends this 
query to an object, this flag is set, since the **cx:dx** passed are 
the object, and don't want to get confused and think that we 
have already travelled the entire circuit. This flag is reset 
before the message is passed onto the next node in the circuit. 

NF_SKIP_NODE  
Set to tell the recipient to forward the message on to the next 
object in the circuit. if reset, and is composite, will forward 
message to first child. If leaf node, will forward to next sibling. 
If is last sibling, will forward to parent passing NF_SKIP_NODE 
set so that parent will forward to sibling or parent.

NF_TRAVEL_CIRCUIT  
Set to force message to be passed through the entire navigation 
circuit, back to the originating object. This is useful for error 
checking, and for the "navigate to previous" case.

**Library:** Objects/visC.def

----------
#### NCCFlagsUnion
    NCCFlagsUnion       union
        NCCFU_char              VisTextCharAttrFlags
        NCCFU_paragraph         VisTextParaAttrFlags
        NCCFU_border            VisTextParaAttrBorderFlags
    NCCFlagsUnion       ends

**Library:** Objects/Text/tCtrlC.def

----------
#### NoteType
    NoteType    etype byte, 0, 2
        NT_INK      enum NoteType
        NT_TEXT     enum NoteType

**Library:** pen.def

----------
#### NotificationType
    NotificationType        struct
        NT_manuf        ManufacturerID
        NT_type         word
    NotificationType        ends

This structure defines a basic GCN notification type that can be passed with 
MSG_META_NOTIFY and MSG_META_NOTIFY_WITH_DATA_BLOCK.

**Library:** Objects/metaC.def

----------
#### NotifyColorChange
    NotifyColorChange       struct
        NCC_color           ColorQuad
        NCC_grayScreen      SystemDrawMask
        NCC_pattern         GraphicPattern
        NCC_flags           NCCFlagsUnion
                                    ;VTCAF_MULTIPLE_COLORS
                                    ;VTCAF_MULTIPLE_GRAY_SCREENS
                                    ;VTCAF_MULTIPLE_PATTERNS
                                    ;   -or-
                                    ;VTCAF_MULTIPLE_BG_COLORS
                                    ;VTCAF_MULTIPLE_BG_GRAY_SCREENS
                                    ;VTCAF_MULTIPLE_BG_PATTERNS
                                    ;   -or-
                                    ;VTPAF_MULTIPLE_BG_COLORS
                                    ;VTPAF_MULTIPLE_BG_GRAY_SCREENS
                                    ;VTPAF_MULTIPLE_BG_PATTERNS
                                    ;   -or-
                                    ;VTPABF_MULTIPLE_BORDER_COLORS
                                    ;VTPABF_MULTIPLE_BORDER_GRAY_SCREENS
                                    ;VTPABF_MULTIPLE_BORDER_PATTERNS
    NotifyColorChange       ends

**Library:** Objects/Text/tCtrlC.def

----------
#### NotifyDisplayChange
    NotifyDisplayChange         struct
        NDC_displayNum      word
        NDC_name            char MAX_DISPLAY_NAME_SIZE dup (?)
        NDC_overlapping     BooleanByte
    NotifyDisplayChange         ends

**Library:** Objects/gDCtrlC.def

----------
#### NotifyDisplayListChange
    NotifyDisplayListChange         struct
        NDLC_counter            word
        NDLC_group              optr
    NotifyDisplayListChange         ends

**Library:** Objects/gDCtrlC.def

----------
#### NotifyDocumentChange
    NotifyDocumentChange            struct
        NDC_attrs               GenDocumentAttrs
        NDC_type                GenDocumentType
        NDC_fileHandle          hptr
        NDC_emptyExists         BooleanByte
        NDC_defaultExists       BooleanByte
    NotifyDocumentChange            ends

**Library:** Objects/gDocCtrl.def

----------
#### NotifyEnabledFlags
    NotifyEnabledFlags      record
        NEF_STATE_CHANGING      :1  ;this is the object whose state is changing
                                :7
    NotifyEnabledFlags      end

**Library:** Objects/genC.def

----------
#### NotifyFloatFormatChange
    NotifyFloatFormatChange         struc
        NFFC_vmFileHan          word
        NFFC_vmBlkHan           word
        NFFC_format             word
        NFFC_count              word
    NotifyFloatFormatChange         ends

**Library:** math.def

----------
#### NotifyFocusWindowKbdStatus
    NotifyFocusWindowKbdStatus      struct
        NFWKS_needsFloatingKbd          word
        NFWKS_kbdPosition               Point<>
        NFWKS_focusWindow               optr
    NFWKS_sysModal                  word

*NFWKS_needsFloatingKbd*
If non-zero, the window needs a floating keyboard - otherwise, 
it already has an embedded keyboard.

*NFWKS_kbdPosition*
The position at which to display the keyboard

*NFWKS_focusWindow*
The OD of the window with the focus. This is used by embedded 
keyboards, so they can enable themselves when their parent 
window has the focus.

*NFWKS_sysModal*
Either zero if window is not sys-modal or 0xffff if it is

**Library:** 

----------
#### NotifyFontAttrChange
    NotifyFontAttrChange            struct
        NFAC_fontWeight                 byte
        NFAC_fontWeightDiffs            byte
        NFAC_fontWidth                  byte
        NFAC_fontWidthDiffs             byte
        NFAC_trackKerning               word
        NFAC_trackKerningDiffs          byte
    NotifyFontAttrChange            ends

**Library:** Objects/Text/tCtrlC.def

----------
#### NotifyFontChange
    NotifyFontChange            struct
        NFC_fontID          FontID
        NFC_diffs           byte
    NotifyFontChange            ends

**Library:** Objects/Text/tCtrlC.def

----------
#### NotifyGenControlStatusChange
    NotifyGenControlStatusChange                struct
        NGCS_controller                 optr
        NGCS_statusChange               GenControlStatusChange
    NotifyGenControlStatusChange                ends

*NGCS_controller* stores the optr of the GenControl object itself. This optr may 
be used to send messages or fetch information from the GenControl (typically 
to add or remove features).

*NGCS_statusChange* stores the type of status change that the GenControl 
object has undergone.

**Library:** Objects/gCtrlC.def

----------
#### NotifyInkHasTarget
    NotifyInkHasTarget          struct
        NIHT_optr           optr
    NotifyInkHasTarget          ends

This structure is sent to objects requesting GWNT_INK_HAS_TARGET 
notification.

**Library:** pen.def

----------
#### NotifyJustificationChange
    NotifyJustificationChange           struct
        NJC_justification       Justification
        NJC_diffs               byte
        NJC_useGeneral          byte    ;if non-zero then use "general" in place
                                        ;of "full" justification.
    NotifyJustificationChange           ends

**Library:** Objects/Text/tCtrlC.def

----------
#### NotifyPageInfoChange
    NotifyPageInfoChange        struct
        NPIC_width          word
        NPIC_height         word
        NPIC_rightMargin    word        ; 13.3 (8* actual value)
        NPIC_leftMargin     word        ; 13.3 (8* actual value)
        NPIC_topMargin      word        ; 13.3 (8* actual value)
        NPIC_bottomMargin   word        ; 13.3 (8* actual value)
    NotifyPageInfoChange        ends

**Library:** pageInfo.def

----------
#### NotifyPageStateChange
    NotifyPageStateChange           struct
        NPSC_firstPage                  word        ;first page
        NPSC_lastPage                   word        ;last page
        NPSC_currentPage                word        ;current page
    NotifyPageStateChange           ends

**Library:** Objects/gPageCC.def

----------
#### NotifyPointSizeChange
    NotifyPointSizeChange           struct
        NPSC_pointSize          WWFixed
        NPSC_diffs              byte
    NotifyPointSizeChange           ends

**Library:** Objects/Text/tCtrlC.def

----------
#### NotifySearchReplaceEnableChange
    NotifySearchReplaceEnableChange                 struct
        NSREC_flags         SearchReplaceEnableFlags
    NotifySearchReplaceEnableChange                 ends

**Library:** Objects/Text/tCtrlC.def

----------
#### NotifySelectStateChange
    NotifySelectStateChange         struct
        NSSC_selectionType                  SelectionDataType
        NSSC_clipboardableSelection         BooleanByte
        NSSC_selectAllAvailable             BooleanByte
        NSSC_deleteableSelection            BooleanByte
        NSSC_pasteable                      BooleanByte
    NotifySelectStateChange         ends

*NSSC_selectionType* determines if a text object has the target and a selection.

*NSSC_clipboardableSelection* stores BB_TRUE if a selection that can be 
copied to the clipboard exist.

*NSSC_selectAllAvailable* stores BB_TRUE if "select all" is allowed.

*NSSC_deleteableSelection* stores BB_TRUE if a selection that can be deleted 
exists.

*NSSC_pasteable* stores BB_TRUE if the current clipboard is "pasteable."

**Library:** Objects/gEditCC.def

----------
#### NotifyTextStyleChange
    NotifyTextStyleChange           struct
        NTSC_styles             TextStyle
        NTSC_indeterminates     TextStyle
    NotifyTextStyleChange           ends

**Library:** Objects/Text/tCtrlC.def

----------
#### NotifyUndoStateChange
    NotifyUndoStateChange           struct
        NUSC_undoTitle          optr
        NUSC_undoType           UndoDescription
    NotifyUndoStateChange           ends

*NUSC_undoTitle* stores the title of the current undo item or 0:0 if there is no 
operation to undo.

**Library:** Objects/gEditCC.def

----------
#### NotifyViewStateChange
    NotifyViewStateChange               struct
        NVSC_origin                 PointDWFixed
        NVSC_docBounds              RectDWord
        NVSC_increment              PointDWord
        NVSC_scaleFactor            PointWWFixed
        NVSC_color                  ColorQuad
        NVSC_attrs                  GenViewAttrs
        NVSC_horizAttrs             GenViewDimensionAttrs
        NVSC_vertAttrs              GenViewDimensionAttrs
        NVSC_inkType                GenViewInkType
        NVSC_contentSize            XYSize
        NVSC_contentScreenSize      XYSize
        NVSC_originRelative         PointDWord
        NVSC_documentSize           PointDWord
    NotifyViewStateChange               ends

**Library:** Objects/gViewCC.def

----------
#### NumberFormatFlags
    NumberFormatFlags       record
                                :7
        NFF_LEADING_ZERO        :1
    NumberFormatFlags       end

**Library:** localize.def

----------
#### NumberType
    NumberType      etype byte, 0, 1
        NT_VALUE        enum NumberType         ; It's just a number
        NT_BOOLEAN      enum NumberType         ; It's a boolean
        NT_DATE_TIME    enum NumberType         ; It's a date/time

**Library:** parse.def

----------
#### ObjChunkFlags
    ObjChunkFlags       record
                                :3
        OCF_VARDATA_RELOC       :1
        OCF_DIRTY               :1
        OCF_IGNORE_DIRTY        :1
        OCF_IN_RESOURCE         :1
        OCF_IS_OBJECT           :1
    ObjChunkFlags       end

**Library:** object.def

----------
#### ObjCompCallType
    ObjCompCallType     etype word, 0, 2
        OCCT_SAVE_PARAMS_TEST_ABORT             enum ObjCompCallType
        OCCT_SAVE_PARAMS_DONT_TEST_ABORT        enum ObjCompCallType
        OCCT_DONT_SAVE_PARAMS_TEST_ABORT        enum ObjCompCallType
        OCCT_DONT_SAVE_PARAMS_DONT_TEST_ABORT   enum ObjCompCallType
        OCCT_ABORT_AFTER_FIRST                  enum ObjCompCallType
        OCCT_COUNT_CHILDREN                     enum ObjCompCallType

**Library:** Objects/metaC.def

----------
#### ObjectTransform
    ObjectTransform     struct
        OT_center           PointDWFixed
        OT_width            WWFixed
        OT_height           WWFixed
        OT_parentWidth      WWFixed
        OT_parentHeight     WWFixed
        OT_transform        GrObjTransMatrix
    ObjectTransform     ends

*OT_center* stores the center of the object in the parent's coordinate system.

*OT_width* stores the width of object in the object's coordinate system

*OT_height* stores the height of object in the object's coordinate system.

*OT_parentWidth* stores the width of the object in the parent's coordinate 
system. This width includes line width and can therefore be used for 
invalidation, etc.

*OT_parentHeight* stores the height of the object in the parent's coordinate 
system. This height includes line height, etc. and can therefore be used for 
invalidation, etc.

**Library:** grobj.def

----------
#### ObjFlushInputQueueNextStop
    ObjFlushInputQueueNextStop          etype word, 0, 2
        OFIQNS_INPUT_MANAGER                enum ObjFlushInputQueueNextStop
        OFIQNS_SYSTEM_INPUT_OBJ             enum ObjFlushInputQueueNextStop
        OFIQNS_INPUT_OBJ_OF_OWNING_GEODE    enum ObjFlushInputQueueNextStop
        OFIQNS_PROCESS_OF_OWNING_GEODE      enum ObjFlushInputQueueNextStop
        OFIQNS_DISPATCH                     enum ObjFlushInputQueueNextStop

OFIQNS__INPUT_MANAGER  
MF_FORCE_QUEUE message to the kernel's input manager 
thread passing OFIQNS_INPUT_OBJ_OF_OWNING_GEODE.

OFIQNS_SYSTEM_INPUT_OBJ  
MF_FORCE_QUEUE message to the System input object 
(usually the GenSystem object), passing 
OFIQNS_INPUT_OBJ_OF_OWNING_GEODE.

OFIQNS_INPUT_OBJ_OF_OWNING_GEODE  
MF_FORCE_QUEUE message next to the InputObj of the geode 
owning the block that the object is in, passing 
OFIQNS_PROCESS_OF_OWNING_GEODE. 

OFIQNS_PROCESS_OF_OWNING_GEODE  
MF_FORCE_QUEUE message next to the process of the geode 
owning the block that the object is in, passing 
OFIQNS_DISPATCH.

OFIQNS_DISPATCH  
Queues are flushed, so FORCE_QUEUE dispatch passed Event.

**Library:** Objects/metaC.def

----------
#### ObjLMemBlockHeader
    ObjLMemBlockHeader          struct
        OLMBH_header                LMemBlockHeader <>
        OLMBH_inUseCount            word
        OLMBH_interactibleCount     word
        OLMBH_output                optr
        OLMBH_resourceSize          word
    ObjLMemBlockHeader          ends

This structure is the standard object block (resource) header that begins 
every object block. Since Object blocks are types of LMem blocks, the first 
entry in the **ObjLMemBlockHeader** must contain a **LMemBlockHeader**.

*OLMBH_header* stores the LMem block header.

*OLMBH_inUseCount* stores the "in use" count for this block. If this count is 
not zero, then the block may not safely be freed.

*OLMBH_interactibleCount* stores the "interactable" count for this block, 
which prevents the block from being swapped. If not zero, then one or more 
objects in the block are either visible to the user or about to be activated by 
the user (e.g. via keyboard shortcut).

*OLMBH_output* stores the optr of the object that will be notified about 
changes in the resource status, such as in-use counts changing to or from 
zero. Messages may be sent to this optr using the TravelOption 
TO_OBJ_BLOCK_OUTPUT.

*OLMBH_resourceSize* stores the size of the object block.

**Library:** object.def

----------
#### ObjRelocation
    ObjRelocation       struct
        OR_type     ObjRelocationType       ; Type of relocation
        OR_offset   word                    ; Offset to relocation
    ObjRelocation       ends

This is the structure of an object relocation table entry (for instance data).

**Library:** object.def

----------
#### ObjRelocationID
    ObjRelocationID     record
        RID_SOURCE          ObjRelocationSource:4
        RID_INDEX           :12
    ObjRelocationID     end

**Library:** object.def

----------
#### ObjRelocationSource
    ObjRelocationSource         etype byte
        ORS_NULL                        enum ObjRelocationSource
        ORS_OWNING_GEODE                enum ObjRelocationSource
        ORS_KERNEL                      enum ObjRelocationSource
        ORS_LIBRARY                     enum ObjRelocationSource
        ORS_CURRENT_BLOCK               enum ObjRelocationSource
        ORS_VM_HANDLE                   enum ObjRelocationSource
        ORS_OWNING_GEODE_ENTRY_POINT    enum ObjRelocationSource
        ORS_NON_STATE_VM                enum ObjRelocationSource
        ORS_UNKNOWN_BLOCK               enum ObjRelocationSource
        ORS_EXTERNAL                    enum ObjRelocationSource

ORS_NULL  
ObjRelocation to zero.

ORS_OWNING_GEODE  
Resource of geode. index is resource ID

ORS_KERNEL  
Kernel entry point

ORS_LIBRARY  
Index is imported library number.

ORS_CURRENT_BLOCK  
Handle of block.

ORS_VM_HANDLE  
Reloc to handle of block saved on the saved list-index is a VM 
iD

ORS_OWNING_GEODE_ENTRY_POINT  
Entry point of owner.

ORS_NON_STATE_VM  
Index is a VM index, vm file handle stored in block header

ORS_UNKNOWN_BLOCK  
Index is a handle>>4

ORS_EXTERNAL  
Internal.

**Library:** object.def

----------
#### ObjRelocationType
    ObjRelocationType           etype byte
        RELOC_END_OF_LIST   enum ObjRelocationType
        RELOC_HANDLE        enum ObjRelocationType  ;resource ID to handle
        RELOC_SEGMENT       enum ObjRelocationType  ;resource ID to segment
        RELOC_ENTRY_POINT   enum ObjRelocationType  ;resource ID/entry #

RELOC_END_OF_LIST  
Relocation from resource ID to handle. The target contains the 
resource identification (described below)

RELOC_HANDLE  
Relocation from resource ID to segment. The target contains 
the resource identification (described below)

RELOC_SEGMENT  
Relocation from resource ID/entry point number to a far 
pointer. The low word of the target contains the resource 
identification and the high word of the target contains the 
entry point number.

RELOC_ENTRY_POINT  
Resource ID/entry number.

**Library:** object.def

----------
#### OldErrorCheckingFlags
    OldErrorCheckingFlags   record
        OECF_REGION             :1  ;Region checking
        OECF_HEAP_FREE_BLOCKS   :1  ;Ensure that all free blocks are 0xcccc
        OECF_LMEM_INTERNAL      :1  ;Internal lmem checking
        OECF_LMEM_FREE_AREAS    :1  ;Ensure that all free areas are 0xcccc
        OECF_LMEM_OBJECT        :1  ;Consistency checks on objects in lmem chunks
        OECF_BLOCK_CHECKSUM     :1  ;Checksum on a particular block
        OECF_GRAPHICS           :1  ;Misc graphics stuff
        OECF_SEGMENT            :1  ;Extensive segment checking
        OECF_NORMAL             :1  ;Misc kernel error checking
        OECF_VMEM               :1  ;VM file consistency
        OECF_APP                :1  ;Application error checking (if implemented
                                    ;by applications)
        OECF_LMEM_MOVE          :1  ;Force lmem blocks to move whenever possible
        OECF_UNLOCK_MOVE        :1  ;Force unlocked blocks to move
        OECF_VMEM_DISCARD       :1  ;Force clean VM blocks to be discarded
        OECF_ANAL_VMEM          :1  ;Extensive VM error checking
        OECF_TEXT               :1
    OldErrorCheckingFlags   end

**Library:** ec.def

----------
#### OperatorStackElement
    OperatorStackElement    struct
        OSE_type        EvalStackOperatorType   ; Type of the operator
        OSE_data        EvalStackOperatorData   ; The associated data
    OperatorStackElement    ends

**Library:** parse.def

----------
#### OperatorType
    OperatorType        etype byte, 0, 1
        OP_RANGE_SEPARATOR              enum OperatorType
        OP_NEGATION                     enum OperatorType
        OP_PERCENT                      enum OperatorType
        OP_EXPONENTIATION               enum OperatorType
        OP_MULTIPLICATION               enum OperatorType
        OP_DIVISION                     enum OperatorType
        OP_MODULO                       enum OperatorType
        OP_ADDITION                     enum OperatorType
        OP_SUBTRACTION                  enum OperatorType
        OP_EQUAL                        enum OperatorType
        OP_NOT_EQUAL                    enum OperatorType
        OP_LESS_THAN                    enum OperatorType
        OP_GREATER_THAN                 enum OperatorType
        OP_LESS_THAN_OR_EQUAL           enum OperatorType
        OP_GREATER_THAN_OR_EQUAL        enum OperatorType
        ;
        ;
        OP_STRING_CONCAT                enum OperatorType
        OP_RANGE_INTERSECTION           enum OperatorType
        ;
        ; The following are graphic versions of existing operators. For example,
        ; OP_NOT_EQUAL_GRAPHIC is the same as OP_NOT_EQUAL, but shows up on screen
        ; as an equals sign with a line through it.
        ;
        OP_NOT_EQUAL_GRAPHIC            enum OperatorType
        OP_DIVISION_GRAPHIC             enum OperatorType
        OP_LESS_THAN_OR_EQUAL_GRAPHIC   enum OperatorType
        OP_GREATER_THAN_OR_EQUAL_GRAPHIC enum OperatorType
        ;
        ; The following are included here because it's convenient. They represent
        ; an as yet undecided operator. The scanner has seen it and recognized it.
        ; The parser will decide which operator it is.
        ;
        ; The problem is that a single lexical token can correspond to two different
        ; operations, depending on the context:
        ; Percent Operator:
        ;   9%  <- Divides the value to the left by 100
        ; Modulo Operator:
        ;   9%2 <- Performs the operation "9 MOD 2"
        ; Negation Operator:
        ;   -5  <- Negates the value to the right
        ; Subtraction Operator:
        ;   3-5 <- Performs the operation "3 MINUS 5"
        ;
        ; Since the scanner has no idea what is coming next in the input stream it
        ; can only return that the operator is undecided.
        ;
        ; These operators should always be the last in the list since none of the
        ; tables depend on them.
        ;
        OP_PERCENT_MODULO               enum OperatorType
        OP_SUBTRACTION_NEGATION         enum OperatorType

**Library:** parse.def

----------
#### OriginChangedParams
    OriginChangedParams         struct
        OCP_origin      PointDWord      ;new origin
        OCP_window      lptr Window     ;window of view
    OriginChangedParams         ends

**Library:** Objects/gViewC.def

----------
#### PACFeatures
    PACFeatures     record
        PACF_WORD_WRAP                  :1
        PACF_COLUMN_BREAK_BEFORE        :1
        PACF_KEEP_PARA_WITH_NEXT        :1
        PACF_KEEP_PARA_TOGETHER         :1
        PACF_KEEP_LINES                 :1
    PACFeatures     end

**Library:** Objects/Text/tCtrlC.def

----------
#### PACToolboxFeatures
    PACToolboxFeatures      record
    PACToolboxFeatures      end

**Library:** Object/Text/tCtrlC.def

----------
#### PageEndCommand
    PageEndCommand      etype   byte
        PEC_FORM_FEED       enum    PageEndCommand  ; 0 = form feed
        PEC_NO_FORM_FEED    enum    PageEndCommand  ; 1 = no form feed

**Library:** graphics.def

----------
#### PageLayout
    PageLayout      union
        PL_paper            PageLayoutPaper
        PL_envelope         PageLayoutEnvelope
        PL_label            PageLayoutLabel
    PageLayout      end

**Library:** spool.def

----------
#### PageLayoutEnvelope
    PageLayoutEnvelope          record
                            :12
        PLE_ORIENTATION     EnvelopeOrientation:1
        PLE_TYPE            PageType:3              ; PT_ENVELOPE
    PageLayoutEnvelope          end

**Library:** spool.def

----------
#### PageLayoutLabel
    PageLayoutLabel         record
                        :1
        PLL_ROWS        :6              ; labels down
        PLL_COLUMNS     :6              ; labels across
        PLL_TYPE        PageType:3      ; PT_LABEL
    PageLayoutLabel         end

**Library:** spool.def

----------
#### PageLayoutPaper
    PageLayoutPaper     record
                            :12
        PLP_ORIENTATION     PaperOrientation:1
        PLP_TYPE            PageType:3          ; PT_PAPER
    PageLayoutPaper     end

**Library:** spool.def

----------
#### PageSetupInfo
    PageSetupInfo       struct
        PSI_meta            VMChainLink
        PSI_pageSize        XYSize          ; In pixels (points)
        PSI_layout          PageLayout
        PSI_numColumns      word
        PSI_columnSpacing   word            ; In points * 8
        PSI_ruleWidth       word            ; In pixels (points)
        ;
        ; The margins are relative to the edges of the page, and are in points * 8
        ;
        PSI_leftMargin      word
        PSI_rightMargin     word
        PSI_topMargin       word
        PSI_bottomMargin    word
    PageSetupInfo       ends

**Library:** Objects/vTextC.def

----------
#### PageSizeControlAttrs
    PageSizeControlAttrs        record
        ; EXTERNAL
        PZCA_ACT_LIKE_GADGET        :1
        PZCA_PAPER_SIZE             :1
        PZCA_INITIALIZE             :1
                                    :5
        ; INTERNAL
        PZCA_NEW_PAGE_TYPE          :1      ;INTERNAL
        PZCA_SWAP_WIDTH_HEIGHT      :1      ;INTERNAL
        PZCA_SIZE_LIST_INITIALIZED  :1      ;INTERNAL
        PZCA_IGNORE_UPDATE          :1      ;INTERNAL
        PZCA_PORTRAIT_VALID         :1
        PZCA_LANDSCAPE_VALID        :1
                                    :2
    PageSizeControlAttrs        end

PZCA_ACT_LIKE_GADGET  
Tells the PageSizeControl object to act like any other generic 
gadget, where one uses messages to set/get the state of the 
object.

PZCA_PAPER_SIZE  
Tell the PageSizeControl to display paper, and not document, 
sizes. Most applications will not want this set.

PZCA_INITIALIZE  
Initialize with the default system values. The flag 
PZCA_ACT_LIKE_GADGET must be set if you want to use this 
attribute.

**Library:** spool.def

----------
#### PageSizeControlChanges
    PageSizeControlChanges          struct
        PSCC_destination        optr        ; destination for message
        PSCC_message            word        ; message to be sent
        ;
        ;   Pass:       SS:BP   = PageSizeReport
        ;               DX      = size PageSizeReport
        ;   Returns:    Nothing
        ;               AX, CX, DX, BP - may destroy
        ;
    PageSizeControlChanges          ends

**Library:** spool.def

----------
#### PageSizeControlFeatures
    PageSizeControlFeatures         record
        PSIZECF_MARGINS         :1      ; not part of default features
        PSIZECF_CUSTOM_SIZE     :1
        PSIZECF_LAYOUT          :1
        PSIZECF_SIZE_LIST       :1
        PSIZECF_PAGE_TYPE       :1
    PageSizeControlFeatures         end

**Library:** spool.def

----------
#### PageSizeControlMaxDimensions
    PageSizeControlMaxDimensions    struct
        PZCMD_width             dword       ; maximum width
        PZCMD_height            dword       ; maximum height
    PageSizeControlMaxDimensions    ends

**Library:** spool.def

----------
#### PageSizeControlToolboxFeatures
    PageSizeControlToolboxFeatures          record
        PSIZECTF_DIALOG_BOX             :1
    PageSizeControlToolboxFeatures          end

**Library:** spool.def

----------
#### PageSizeReport
    PageSizeReport          struct
        PSR_width       dword               ; width of the page
        PSR_height      dword               ; height of the page
        PSR_layout      PageLayout          ; layout options
        PSR_margins     PCMarginParams      ; document margins
    PageSizeReport          ends

**Library:** spool.def

----------
#### PageType
    PageType        etype word, 0, 2
        PT_PAPER            enum PageType
        PT_ENVELOPE         enum PageType
        PT_LABEL            enum PageType

**Library:** print.def

----------
#### Palette
    Palette     struct
        P_entries       word 16     ; Number of 3-byte entries in palette.
    Palette     ends

This structure stores the custom palettes allocated by **GrCreatePalette** and 
associated with windows.

**Library:** color.def

----------
#### PaperOrientation
    PaperOrientation        etype byte, 0, 1
        PO_PORTRAIT             enum PaperOrientation
        PO_LANDSCAPE            enum PaperOrientation

**Library:** print.def

----------
#### ParserFlags
    ParserFlags     record
        ;
        ; These are initialized by the parser. They are initialized to zero.
        ;
        PF_HAS_LOOKAHEAD            :1  ; The next token to get is the look-ahead 
                                        ; token.
        PF_CONTAINS_DISPLAY_FUNC    :1  ; Set: This expression contains a function
                                        ; which should be evaluated when the
                                        ; result of the expression is displayed.
        PF_OPERATORS                :1  ; Set: Allow operators.
        PF_NUMBERS                  :1  ; Set: Allow numbers.
        PF_CELLS                    :1  ; Set: Allow cell references.
        PF_FUNCTIONS                :1  ; Set: Allow functions.
        PF_NAMES                    :1  ; Set: Allow names.
        PF_NEW_NAMES                :1  ; Set: Allow new names (app only).
    ParserFlags     end

**Library:** parse.def

----------
#### ParserParameters
    ParserParameters        struct
        ;
        ; Applications should initialize these fields before calling ParseString
        ;
        PP_common               CommonParameters <>
        ;
        ; Possible callbacks:
        ; CT_FUNCTION_TO_TOKEN
        ; CT_NAME_TO_TOKEN
        ;
        PP_parserBufferSize     word            ; Size of the buffer
        ;
        ; Fields below this point are initialized by ParseString
        ;
        PP_flags                ParserFlags     ; Parsing flags
        PP_textPtr              fptr.char       ; Pointer to text
        PP_currentToken         ScannerToken    ; Current token
        PP_lookAheadToken       ScannerToken    ; Look ahead token

        PP_error                ParserScannerEvaluatorError
        PP_tokenStart           word            ; Offset to start of token
        PP_tokenEnd             word            ; Offset to end of token
    ParserParameters        ends

The parser allocates this structure on the stack when performing parsing 
operations such as **ParseString**.

**Library:** parse.def

----------
#### ParserScannerEvaluatorError
    ParserScannerEvaluatorError             etype byte, 0, 1
        ;
        ; Scanner errors
        ;
        PSEE_BAD_NUMBER                 enum ParserScannerEvaluatorError
        PSEE_BAD_CELL_REFERENCE         enum ParserScannerEvaluatorError
        PSEE_NO_CLOSE_QUOTE             enum ParserScannerEvaluatorError
        PSEE_COLUMN_TOO_LARGE           enum ParserScannerEvaluatorError
        PSEE_ROW_TOO_LARGE              enum ParserScannerEvaluatorError
        PSEE_ILLEGAL_TOKEN              enum ParserScannerEvaluatorError
        ;
        ; Parser errors
        ;
        PSEE_GENERAL                    enum ParserScannerEvaluatorError
        PSEE_TOO_MANY_TOKENS            enum ParserScannerEvaluatorError
        PSEE_EXPECTED_OPEN_PAREN        enum ParserScannerEvaluatorError
        PSEE_EXPECTED_CLOSE_PAREN       enum ParserScannerEvaluatorError
        PSEE_BAD_EXPRESSION             enum ParserScannerEvaluatorError
        PSEE_EXPECTED_END_OF_EXPRESSION enum ParserScannerEvaluatorError
        PSEE_MISSING_CLOSE_PAREN        enum ParserScannerEvaluatorError
        PSEE_UNKNOWN_IDENTIFIER         enum ParserScannerEvaluatorError
        PSEE_NOT_ENOUGH_NAME_SPACE      enum ParserScannerEvaluatorError
        ;
        ; Serious evaluator errors
        ;
        PSEE_OUT_OF_STACK_SPACE         enum ParserScannerEvaluatorError
        PSEE_NESTING_TOO_DEEP           enum ParserScannerEvaluatorError
        ;
        ; Evaluator errors that are returned as the result of formulas.
        ; These are returned on the argument stack.
        ;
        PSEE_ROW_OUT_OF_RANGE           enum ParserScannerEvaluatorError
        PSEE_COLUMN_OUT_OF_RANGE        enum ParserScannerEvaluatorError
        PSEE_FUNCTION_NO_LONGER_EXISTS  enum ParserScannerEvaluatorError
        PSEE_BAD_ARG_COUNT              enum ParserScannerEvaluatorError
        PSEE_WRONG_TYPE                 enum ParserScannerEvaluatorError
        PSEE_DIVIDE_BY_ZERO             enum ParserScannerEvaluatorError
        PSEE_UNDEFINED_NAME             enum ParserScannerEvaluatorError
        PSEE_CIRCULAR_REF               enum ParserScannerEvaluatorError
        PSEE_CIRCULAR_DEP               enum ParserScannerEvaluatorError
        PSEE_CIRC_NAME_REF              enum ParserScannerEvaluatorError
        PSEE_NUMBER_OUT_OF_RANGE        enum ParserScannerEvaluatorError
        PSEE_GEN_ERR                    enum ParserScannerEvaluatorError
        PSEE_NA                         enum ParserScannerEvaluatorError
        ;
        ; Dependency errors
        ;
        PSEE_TOO_MANY_DEPENDENCIES      enum ParserScannerEvaluatorError
        ;
        ; Applications can define errors too, they start here.
        ;
        PSEE_FIRST_APPLICATION_ERROR    enum ParserScannerEvaluatorError, 0xc0
        ;
        ; !!! NOTE !!!
        ; These PSEE_ errors map directly to the floating point errors
        ; Any change in the float library errors require corresponding
        ; changes here.
        ;
        PSEE_FLOAT_POS_INFINITY         enum ParserScannerEvaluatorError, 250
        PSEE_FLOAT_NEG_INFINITY         enum ParserScannerEvaluatorError
        PSEE_FLOAT_GEN_ERR              enum ParserScannerEvaluatorError

**Library:** parse.def

----------
#### ParserToken
    ParserToken         struct
        PT_type     ParserTokenType             ; Type of token data
        PT_data     ParserTokenData             ; The data itself
    ParserToken         ends

**Library:** parse.def

----------
#### ParserTokenCellData
    ParserTokenCellData             struct
        PTCD_cellRef            CellReference <>
    ParserTokenCellData             ends

**Library:** parse.def

----------
#### ParserTokenData
    ParserTokenData     union
        PTD_number          ParserTokenNumberData
        PTD_string          ParserTokenStringData
        PTD_name            ParserTokenNameData
        PTD_cell            ParserTokenCellData
        PTD_function        ParserTokenFunctionData
        PTD_operator        ParserTokenOperatorData
    ParserTokenData     end

**Library:** parse.def

----------
#### ParserTokenFunctionData
    ParserTokenFunctionData     struct
        PTFD_functionID             word    ; Identifier for the function
    ParserTokenFunctionData     ends

**Library:** 

----------
#### ParserTokenNameData
    ParserTokenNameData         struct
        PTND_name       word        ; The token describing the name
    ParserTokenNameData         ends

**Library:** parse.def

----------
#### ParserTokenNumberData
    ParseTokenNumberData            struct
        PTND_value          FloatNum <>     ; 8 byte constant
    ParseTokenNumberData            ends

**Library:** parse.def

----------
#### ParserTokenOperatorData
    ParserTokenOperatorData             struct
        PTOD_operatorID         OperatorType    ; The operator ID.
    ParserTokenOperatorData             ends

**Library:** parse.def

----------
#### ParserTokenStringData
    ParserTokenStringData           struct
        PTSD_length         word        ; Length of the string
    ParserTokenStringData           ends

**Library:** parse.def

----------
#### ParserTokenType
    ParserTokenType     etype byte, 0, 1
        PARSER_TOKEN_NUMBER                 enum ParserTokenType
        PARSER_TOKEN_STRING                 enum ParserTokenType
        PARSER_TOKEN_CELL                   enum ParserTokenType
        PARSER_TOKEN_END_OF_EXPRESSION      enum ParserTokenType
        PARSER_TOKEN_OPEN_PAREN             enum ParserTokenType
        PARSER_TOKEN_CLOSE_PAREN            enum ParserTokenType
        PARSER_TOKEN_NAME                   enum ParserTokenType
        ;
        ; All the items above are in common with the ScannerTokenType list.
        ; You can add or delete items below this point without changing
        ; the other table.
        ;
        PARSER_TOKEN_FUNCTION               enum ParserTokenType
        PARSER_TOKEN_CLOSE_FUNCTION         enum ParserTokenType
        PARSER_TOKEN_ARG_END                enum ParserTokenType
        PARSER_TOKEN_OPERATOR               enum ParserTokenType

**Library:** parse.def

----------
#### PASCFeatures
    PASCFeatures        record
        PASCF_SPACE_ON_TOP          :1
        PASCF_SPACE_ON_BOTTOM       :1
    PASCFeatures        end

**Library:** Objects/Text/tCtrlC.def

----------
#### PASCToolboxFeatures
    PASCToolboxFeatures         record
    PASCToolboxFeatures         end

**Library:** Objects/Text/tCtrlC.def

----------
#### PathCombineType
    PathCombineType     etype word
        PCT_NULL            enum PathCombineType    ; destroy current
        PCT_REPLACE         enum PathCombineType    ; replace current
        PCT_UNION           enum PathCombineType    ; add to current
        PCT_INTERSECTION    enum PathCombineType    ; intersect with curr

**Library:** graphics.def

----------
#### PathCompareType
    PathCompareType     etype byte
        PCT_EQUAL           enum PathCompareType
        PCT_SUBDIR          enum PathCompareType
        PCT_UNRELATED       enum PathCompareType
        PCT_ERROR           enum PathCompareType

PCT_EQUAL  
The 2 paths are equal.

PCT_SUBDIR  
Path 2 is a subdirectory of path 1.

PCT_UNRELATED  
Either the 2 paths are unrelated, or path 1 is a subdirectory of 
path 2.

PCT_ERROR  
Some error occurred while parsing one of the paths (i.e., one of 
the paths was not found, etc.).

**Library:** file.def

----------
#### PatternType
    PatternType     etype byte
        PT_SOLID                enum PatternType    
        PT_SYSTEM_HATCH         enum PatternType    
        PT_SYSTEM_BITMAP        enum PatternType    
        PT_USER_HATCH           enum PatternType    
        PT_USER_BITMAP          enum PatternType    
        PT_CUSTOM_HATCH         enum PatternType    
        PT_CUSTOM_BITMAP        enum PatternType    

PT_SOLID  
Solid pattern. Passed in AH: Nothing.

PT_SYSTEM_HATCH  
System-defined hatch pattern. Passed in AH: SystemHatch.

PT_SYSTEM_BITMAP  
System-defined tiled bitmap. Passed in AH: SystemBitmap.

PT_USER_HATCH  
User-defined hatch pattern. Passed in AH: 0-255.

PT_USER_BITMAP  
User-defined tiled bitmap. Passed in AH: 0-255.

PT_CUSTOM_HATCH  
Application-custom hatch pattern. Passed in AH: Nothing.

PT_CUSTOM_BITMAP  
Appl-custom tiled bitmap.

**Library:** graphics.def

----------
#### PCComInitFlags
    PCComInitFlags record
        PCCIF_NOTIFY_OUTPUT     :1  ; notify caller of output
        PCCIF_NOTIFY_EXIT       :1  ; notify caller of remote exit
                                :14
    PCComInitFlags end

**Library:** pccom.def

----------
#### PCComReturnType
    PCComReturnType etype byte
        PCCRT_NO_ERROR                  enum PCComReturnType
        PCCRT_CANNOT_LOAD_SERIAL_DRIVER     enum PCComReturnType
        PCCRT_CANNOT_CREATE_THREAD          enum PCComReturnType
        PCCRT_CANNOT_ALLOC_STREAM           enum PCComReturnType
        PCCRT_ALREADY_INITIALIZED           enum PCComReturnType

**Library:** pccom.def

----------
#### PCDocSizeParams
    PCDocSizeParams         struct
        PCDSP_width     dword (?)       ; width of the document
        PCDSP_height    dword (?)       ; height of the document
    PCDocSizeParams         ends

**Library:** spool.def

----------
#### PCMarginParams
    PCMarginParams      struct
        PCMP_left           word (?)            ; left margin
        PCMP_top            word (?)            ; top margin
        PCMP_right          word (?)            ; right margin
        PCMP_bottom         word (?)            ; bottom margin
    PCMarginParams      ends

**Library:** print.def

----------
#### PCProgressType
    PCProgressType          etype word, 0, 2
        PCPT_PAGE       enum PCProgressType     ; change page number
        PCPT_PERCENT    enum PCProgressType     ; change percent done
        PCPT_TEXT       enum PCProgressType     ; change text message

**Library:** spool.def

----------
#### PenInputDisplayType
    PenInputDisplayType         etype word
        PIDT_KEYBOARD                   enum PenInputDisplayType
        PIDT_CHAR_TABLE                 enum PenInputDisplayType
        PIDT_CHAR_TABLE_SYMBOLS         enum PenInputDisplayType
        PIDT_CHAR_TABLE_INTERNATIONAL   enum PenInputDisplayType
        PIDT_CHAR_TABLE_MATH            enum PenInputDisplayType
        PIDT_CHAR_TABLE_CUSTOM          enum PenInputDisplayType
        PIDT_HWR_ENTRY_AREA             enum PenInputDisplayType

**Library:** Objects/gPenICC.def

----------
#### PLInit
    PLInit  struct
        PLI_align           byte
        PLI_message         word
        PLI_point           PointDWFixed
        PLI_instructions    PriorityListInstructions
        PLI_maxElements     word
        PLI_class           fptr.ClassStruct
    PLInit  ends

**Library:** grobj.def

----------
#### Point
    Point   struct
        P_x sword
        P_y sword
    Point   ends

**Library:** graphics.def

----------
#### PointDWFixed
    PointDWFixed        struct
        PDF_x       DWFixed
        PDF_y       DWFixed
    PointDWFixed        ends

This structure stores a point (in graphic coordinates) where each coordinate 
is in terms of a **DWFixed** value.

**Library:** graphics.def

----------
#### PointDWord
    PointDWord      struct
        PD_x    sdword
        PD_y    sdword
    PointDWord      ends

This structure stores a point (in graphic coordinates) where each coordinate 
is in terms of a signed dword value.

**Library:** graphics.def

----------
#### PointerDef
    PointerDef      struct
        PD_width        PointerDefWidth
        PD_height       byte
        PD_hotX         sbyte
        PD_hotY         sbyte
    PointerDef      ends

This structure defines a mouse pointer.

*PD_width* and *PD_height* store the width and height of the cursor, in points.

*PD_hotX* and *PD_hotY* store the horizontal and vertical offset to the "hot spot" 
of the pointer. These offsets are relative to the upper left corner of the pointer.

**Library:** graphics.def

----------
#### PointerDefWidth
    PointerDefWidth record
        PDW_ALWAYS_SHOW_PTR     :1
        ; flag, set in BUSY cursors & any other cursors that should be shown
        ; for status's sake, regardless of whether the ptr image is normally
        ; hidden or not (such as in keyboard-only or ink-only systems).
        ; Interpreted, implemented by Input Manager -- Video drivers should
        ; ignore. 
        PDW_WIDTH               :7
        ; width of cursor
    PointerDefWidth end

**Library:** graphics.def

----------
#### PointerModes
    PointerModes        record
        PM_HANDLES_RESIZE                   :1
        PM_HANDLES_ROTATE                   :1
        PM_POINTER_IS_ACTION_OBJECT         :1
    PointerModes        end

**Library:** grobj.def

----------
#### PointWBFixed
    PointWBFixed        struct
        PWBF_x      WBFixed
        PWBF_y      WBFixed
    PointWBFixed        ends

This structure stores a point (in graphic coordinates) where each coordinate 
is in terms of a **WBFixed** value.

**Library:** graphics.def

----------
#### PointWWFixed
    PointWWFixed        struct
        PF_x        WWFixed
        PF_y        WWFixed
    PointWWFixed        ends

This structure stores a point (in graphic coordinates) where each coordinate 
is in terms of a **WWFixed** value.

**Library:** graphics.def

----------
#### PrefAttributes
    PrefAttributes      record
        PA_REBOOT_IF_CHANGED            :1
        PA_LOAD_IF_USABLE               :1
        PA_SAVE_IF_USABLE               :1
        PA_SAVE_IF_ENABLED              :1
        PA_SAVE_IF_CHANGED              :1
                                        :3
    PrefAttributes      end

PA_REBOOT_IF_CHANGED  
This bit signals that changes in the state of this object, or this 
object's children require a system reboot to take effect. In a 
PrefDialogClass object, if this bit is set, then all children will 
be queried for reboot status (using 
MSG_PREF_GET_REBOOT_INFO), and if a reboot is required, 
PrefMgr will be notified. 

PA_LOAD_IF_USABLE  
Load options only if this object is usable (this is ON by default).

PA_SAVE_IF_USABLE  
Save options only if this object is usable (this is ON by default).

PA_SAVE_IF_ENABLED  
Save options only if this object is enabled.

PA_SAVE_IF_CHANGED  
Save options only if this object has changed.

**Library:**  config.def

----------
#### PrefDialogChangeType
    PrefDialogChangeType            etype word, 0
        PDCT_OPEN           enum PrefDialogChangeType
        PDCT_CLOSE          enum PrefDialogChangeType
        PDCT_DESTROY        enum PrefDialogChangeType
        PDCT_RESTART        enum PrefDialogChangeType
        PDCT_SHUTDOWN       enum PrefDialogChangeType

**Library:** config.def

----------
#### PrefEnableData
    PrefEnableData          struct
        PED_item        word
        PED_lptr        lptr
        PED_flags       PrefEnableFlags
    PrefEnableData          ends

*PED_item* stores the identifier of the item that controls enabling/disabling of 
the object. If the identifier is GIGS_NONE, then the action will be performed 
if no items are selected.

*PED_lptr* stores a pointer to the object that is to be enabled or disabled.

**Library:** config.def

----------
#### PrefEnableFlags
    PrefEnableFlags     record
        PEF_DISABLE_IF_SELECTED         :1
        PEF_DISABLE_IF_NONE             :1
                                        :6
        PrefEnableFlags     end

PEF_DISABLE_IF_SELECTED  
If set, disable the object if the associated item is selected, 
otherwise do the opposite.

PEF_DISABLE_IF_NONE  
If this flag is set, then the *PED_item* field is ignored. Instead, 
the item group will disable the specified object if no items are 
selected-or if there are no items in the list.

**Library:** config.def

----------
#### PrefInitFileFlags
    PrefInitFileFlags       record
        PIFF_USE_ITEM_STRINGS           :1
        PIFF_USE_ITEM_MONIKERS          :1
        PIFF_APPEND_TO_KEY              :1
                                        :5
    PrefInitFileFlags       end

PIFF_USE_ITEM_STRINGS  
If set, then the item group's children must be of class 
**PrefStringItemClass**, and their strings will be used to 
interact with the init file.

PIFF_USE_ITEM_MONIKERS  
If set, then the monikers of the items are used to interact with 
the init file.

PIFF_APPEND_TO_KEY  
If set, the strings in this list will be added to strings that may 
already exist for this key.

**Library:** config.def

----------
#### PrefInteractionAttrs
    PrefInteractionAttrs record
        PIA_LOAD_OPTIONS_ON_INITIATE    :1
        PIA_SAVE_OPTIONS_ON_APPLY       :1
                                        :6
    PrefInteractionAttrs    end

PIA_LOAD_OPTIONS_ON_INITIATE  
If set, then the dialog will send MSG_PREF_INIT, followed by 
MSG_META_LOAD_OPTIONS to itself when it receives a 
MSG_GEN_INTERACTION_INITIATE.

PIA_SAVE_OPTIONS_ON_APPLY  
This flag is normally OFF, to allow non-dialog prefInteraction 
objects to reside inside other interactions without duplicate 
SAVE_OPTIONS messages being sent. This flag is normally on 
for objects of **PrefDialogClass**.

**Library:** config.def

----------
#### PrefItemGroupStringVars
    PrefItemGroupStringVars struct
        PIGSV_endPtr            nptr.char
        PIGSV_selections        word PREF_ITEM_GROUP_MAX_SELECTIONS dup (?)
        PIGSV_numSelections     word
        PIGSV_buffer            char PREF_ITEM_GROUP_STRING_BUFFER_SIZE dup (?)

**Library:** config.def

----------
#### PrefMgrFeatures
    PrefMgrFeatures     record
        PMF_HARDWARE        :1
        PMF_SYSTEM          :1
        PMF_NETWORK         :1
        PMF_USER            :1
                            :12
    PrefMgrFeatures     end

PMF_HARDWARE  
These settings are for a user who has permissions to actually change the 
configuration of the workstation. In a network environment where users log 
in to different machines at different times, normal users would be prevented 
from changing the mouse & video drivers, etc.

PMF_SYSTEM  
These changes are more complex & potentially more damaging than the basic 
"user" changes, therefore, some users may be prevented from using these 
settings.

PMF_NETWORK  
Network settings - generally only the system administrator will see these 
settings.

PMF_USER  
These are basic user changes - normally this flag works the opposite way of 
the other flags - by default all UI is "on", but if the user flag is off, then some 
basic UI might go away. This would allow a network administrator, for 
example, to look at a scaled-down, "network-only" prefmgr.

**Library:** config.def

----------
#### PrefModuleEntryType
    PrefModuleEntryType         etype word, 0, 1
        PMET_FETCH_UI               enum PrefModuleEntryType 
        ;
        ; Return the OD of the top-most object in the UI tree.
        ; All UI *must* be in the same segment as this object. The UI tree
        ; will be duplicated by the application, and added to the app's
        ; generic tree.
        ;
        ; Pass: nothing
        ; Return: ^ldx:ax - OD of root of UI tree.
        ; Destroy: nothing
        ;
        PMET_GET_MODULE_INFO        enum PrefModuleEntryType
        ; Return information about this module that will be used to determine
        ; whether to display it on-screen, what it will look like, etc. 
        ;
        ; Pass: ds:si - pointer to a PrefModuleInfo buffer to be filled in
        ; Return: -- buffer filled in
        ; Destroy: ax, bx
        ;

Entry points for the Preferences Modules. Each module (library) must have 
the following routines exported in its .gp file, in the following order, as the 
first routines exported from that library.

**Library:** config.def

----------
#### PrefModuleInfo
    PrefModuleInfo struct
        PMI_requiredFeatures        PrefMgrFeatures <>
        ; Features that MUST be set for this module to appear in PrefMgr
        PMI_prohibitedFeatures      PrefMgrFeatures <>
        ; Features that MUST NOT be set for this module to appear.
        PMI_minLevel                UIInterfaceLevel    0
        ; Minimum user level required for this module to appear.
        ; Currently not implemented by PrefMgr -- should be set to zero by
        ; module.
        PMI_maxLevel                UIInterfaceLevel    UIInterfaceLevel
        ; Minimum user level required for this module to appear.
        ; Currently not implemented by PrefMgr. Should be set to
        ; the maximum value by module.
        PMI_monikerList             optr
        ; Moniker list in a shared, lmem, read-only resource that will be
        ; used as the module's trigger
        PMI_monikerToken            GeodeToken
        ; A unique GeodeToken that will be used to enter the module's
        ; moniker list into the token database. This is done so that the
        ; module is only called with PMET_GET_MODULE_INFO the first time
        ; it is encountered by PrefMgr - all subsequent times, the
        ; necessary information is cached.
    PrefModuleInfo ends

**Library:** config.def

----------
#### PrefTimeDateControlFeatures
    PrefTimeDateControlFeatures     record
        PTDCF_DATE      :1
        PTDCF_TIME      :1
    PrefTimeDateControlFeatures     end

**Library:** config.def

----------
#### PrefTimeDateControlScreen
    PrefTimeDateControlScreen       etype   word, 0, 2
        PTDCS_TIME_DATE     enum    PrefTimeDateControlScreen

**Library:** config.def

----------
#### PrefTocExtraEntry
    PrefTocExtraEntry       struct
        PTEE_item       lptr.char
        PTEE_driver     lptr.char
        PTEE_info       word
    PrefTocExtraEntry       ends

*PTEE_item* stores the lptr of the item name. For device lists, this is the device. 
For others, this is the filename.

*PTEE_driver* stores the driver name (for device lists only).

*PTEE_info* stores an extra word of information.

**Library:** config.def

----------
#### PrefTriggerAction
    PrefTriggerAction       struct
        PTA_message     word
        PTA_dest        optr
    PrefTriggerAction       ends

**Library:** config.def

----------
#### PrefVMMapBlock
    PrefVMMapBlock  struct 
        PVMMB_root      fptr
    PrefVMMapBlock  ends

Map block for a VM file this object can handle.

*PVMMB_root* is the root of the object tree contained in the VM file. Segment 
portion is VM block handle

**Library:** config.def

----------
#### PrintControlAttrs
    PrintControlAttrs       record
                                :1
        PCA_SEE_IF_DOC_WILL_FIT :1      ; check if document will fit on paper
        PCA_MARK_APP_BUSY       :1      ; mark busy while application is printing
        PCA_VERIFY_PRINT        :1      ; indicate we want to verify before 
                                        ; printing
        PCA_SHOW_PROGRESS       :1      ; show the print progress dialog box
        PCA_PROGRESS_PERCENT    :1      ; show progress by percentage completed
        PCA_PROGRESS_PAGE       :1      ; show progress by page completed
        PCA_FORCE_ROTATION      :1      ; Force rotation of output
        PCA_COPY_CONTROLS       :1      ; Copy controls are available
        PCA_PAGE_CONTROLS       :1      ; Page range controls are available
        PCA_QUALITY_CONTROLS    :1      ; Print quality controls are available
        PCA_USES_DIALOG_BOX     :1      ; A print dialog box should appear
        PCA_GRAPHICS_MODE       :1      ; Supports graphics mode output
        PCA_TEXT_MODE           :1      ; Supports text mode output
        PCA_DEFAULT_QUALITY     PrintQualityEnum:2  ; default print quality
    PrintControlAttrs       end

**Library:** spool.def

----------
#### PrintControlFeatures
    PrintControlFeatures            record
        PRINTCF_PRINT_TRIGGER           :1      ; wants a print trigger
        PRINTCF_FAX_TRIGGER             :1      ; wants a fax trigger
    PrintControlFeatures            end

**Library:** spool.def

----------
#### PrintControlStatus
    PrintControlStatus      etype word
        PCS_PRINT_BOX_VISIBLE       enum PrintControlStatus ; Print DB is on screen
        PCS_PRINT_BOX_NOT_VISIBLE   enum PrintControlStatus ; Print DB not on screen

**Library:** spool.def

----------
#### PrintControlToolboxFeatures
    PrintControlToolboxFeatures             record
        PRINTCTF_PRINT_TRIGGER      :1      ; wants a print tool trigger
        PRINTCTF_FAX_TRIGGER        :1      ; wants a fax tool trigger
    PrintControlToolboxFeatures             end

**Library:** spool.def

----------
#### PrinterDriverType
    PrinterDriverType       etype byte, 0
        PDT_PRINTER         enum PrinterDriverType
        PDT_PLOTTER         enum PrinterDriverType
        PDT_FACSIMILE       enum PrinterDriverType
        PDT_CAMERA          enum PrinterDriverType
        PDT_OTHER           enum PrinterDriverType
        PDT_ALL             equ -1          ; all printers of all types

**Library:** print.def

----------
#### PrinterMode
    PrinterMode     etype byte, 0, 2
        PM_GRAPHICS_LOW_RES enum PrinterMode    ; lowest quality...fastest...
        PM_GRAPHICS_MED_RES enum PrinterMode    ; medium quality...slower...
        PM_GRAPHICS_HI_RES  enum PrinterMode    ; best quality...slowest...
        PM_TEXT_DRAFT       enum PrinterMode    ; fastest ascii output
        PM_TEXT_NLQ         enum PrinterMode    ; best quality ascii output

        PM_FIRST_TEXT_MODE  equ PM_TEXT_DRAFT   ; equate to make the code easier

**Library:** print.def

----------
#### PrinterOutputModes
    PrinterOutputModes      record
        POM_unused              :3      ; leave these bits alone!!!
        POM_GRAPHICS_LOW        :1      ; Graphics mode low quality available
        POM_GRAPHICS_MEDIUM     :1      ; Graphics mode medium quality available 
        POM_GRAPHICS_HIGH       :1      ; Graphics mode high quality available 
        POM_TEXT_DRAFT          :1      ; Character mode draft quality available 
        POM_TEXT_NLQ            :1      ; Character mode NLQ quality available 
    PrinterOutputModes      end

**Library:** spool.def

----------
#### PrintQualityEnum
    PrintQualityenum    etype byte, 0, 1
        PQT_HIGH        enum PrintQualityenum       ; default to high
        PQT_MEDIUM      enum PrintQualityenum       ; default to medium
        PQT_LOW         enum PrintQualityenum       ; default to low

**Library:** spool.def

----------
#### PrintStatusFlags
    PrintStatusFlags        record
        PSF_FAX_AVAILABLE       :1      ; set if a fax driver is available
                                :3
        PSF_ABORT               :1      ; user wants to abort printing
        PSF_RECEIVED_COMPLETED  :1      ; MSG_PC_PRINTING_COMPLETED received
        PSF_RECEIVED_NAME       :1      ; MSG_PC_SET_DOC_NAME received
        PSF_VERIFIED            :1      ; PSG_PC_VERIFY_? received
    PrintStatusFlags        end

**Library:** spool.def

----------
#### PriorityList
    PriorityList        struct
        PL_message          word
        PL_point            PointDWFixed
        PL_instructions     PriorityListInstructions
        PL_class            fptr.ClassStruct
        PL_numElements      word
        PL_maxElements      word
        PL_list             lptr
    PriorityList        ends

*PL_message* stores the method to send to each object.

*PL_point* stores the document coordinates to be examined by the object.

*PL_instructions* stores the instructions for the processing of objects.

*PL_class* stores the class of object to be used (based on the specific 
instructions passed in *PL_instructions*).

*PL_numElements* stores the number of elements currently in the list.

*PL_maxElements* stores the maximum number of elements allowed in the 
list.

*PL_list* stores the chunk handle of the list chunk array.

**Library:** grobj.def

----------
#### PriorityListElement
    PriorityListElement         struct
        PLE_od          optr
        PLE_priority    byte
        PLE_other       byte
    PriorityListElement         ends

**Library:** grobj.def

----------
#### PriorityListInstructions
    PriorityListInstructions            record
        PLI_CHECK_SELECTION_HANDLE_BOUNDS               :1
        PLI_ONLY_PROCESS_SELECTED                       :1
        PLI_ONLY_PROCESS_CLASS                          :1
        PLI_ONLY_INSERT_CLASS                           :1
        PLI_STOP_AT_FIRST_HIGH                          :1
        PLI_ONLY_INSERT_HIGH                            :1
        PLI_DONT_INSERT_OBJECTS_WITH_SELECTION_LOCK     :1
    PriorityListInstructions            end

PLI_CHECK_SELECTION_HANDLE_BOUNDS  
Do trivial reject check on bounds of objects that include the 
selection handles, instead of the normal parent bounds which 
are only guaranteed to surround the image.

PLI_ONLY_PROCESS_SELECTED  
Only send messages to objects that are in selection list.

PLI_ONLY_PROCESS_CLASS  
Only send messages to objects of class.

PLI_ONLY_INSERT_CLASS  
Only insert items of class into priority list.

PLI_STOP_AT_FIRST_HIGH  
Stop processing children after an object evaluates high.

PLI_ONLY_INSERT_HIGH  
Only insert objects that evaluate high.

PLI_DONT_INSERT_OBJECTS_WITH_SELECTION_LOCK  
Don't insert objects that have their selection lock set. These 
objects must return EPN_SELECTION_LOCK_SET.

**Library:** grobj.def

----------
#### ProcessCallRoutineParams
ProcessCallRoutineParams        struct
PCRP_address            fptr
PCRP_dataAX             word
PCRP_dataBX             word
PCRP_dataCX             word
PCRP_dataDX             word
PCRP_dataSI             word
PCRP_dataDI             word
ProcessCallRoutineParams        ends

**Library:** processC.def

----------
#### ProtocolNumber
    ProtocolNumber      struct
        PN_major            word
        PN_minor            word
    ProtocolNumber      ends

This structure defines the protocol level of a file, geode, or document.

*PN_major* represents the most significant compatibility comparisons. If the 
major protocol is different between two items, they are incompatible.

*PN_minor* represents less significant differences. If minor protocols are 
different, the two items may or may not be compatible.

**Library:** geode.def

----------
#### PSCFeatures
    PSCFeatures     record
        PSCF_9              :1
        PSCF_10             :1
        PSCF_12             :1
        PSCF_14             :1
        PSCF_18             :1
        PSCF_24             :1
        PSCF_36             :1
        PSCF_54             :1
        PSCF_72             :1
        PSCF_SMALLER        :1
        PSCF_LARGER         :1
        PSCF_CUSTOM_SIZE    :1
    PSCFeatures     end

**Library:** Objects/Text/tCtrlC.def

----------
#### PSCToolboxFeatures
    PSCToolboxFeatures      record
        PSCTF_9         :1
        PSCTF_10        :1
        PSCTF_12        :1
        PSCTF_14        :1
        PSCTF_18        :1
        PSCTF_24        :1
        PSCTF_36        :1
        PSCTF_54        :1
        PSCTF_72        :1
        PSCTF_SMALLER   :1
        PSCTF_LARGER    :1
    PSCToolboxFeatures      end

**Library:** Objects/Text/tCtrlC.def

----------
#### PtrImageLevel
    PtrImageLevel       etype word, 0
        PIL_SYSTEM          enum PtrImageLevel
        PIL_1               enum PtrImageLevel
        PIL_FLOW            enum PtrImageLevel
        PIL_3               enum PtrImageLevel
        PIL_GEODE           enum PtrImageLevel
        PIL_5               enum PtrImageLevel
        PIL_GADGET          enum PtrImageLevel
        PIL_7               enum PtrImageLevel
        PIL_WINDOW          enum PtrImageLevel
        PIL_DEFAULT         enum PtrImageLevel

Enumerated type for ptr image level. Each level may specify a particular 
mouse ptr image, or specify that the level does not currently have an image. 
The first (starting at lowest enumerated value) level which has a ptr image 
declared will be used at any given moment in time.

PIL_SYSTEM  
PIL_1  
PIL_FLOW  
Used for UI quick transfer move/copy cursors.

PIL_3  
PIL_GEODE  
Overriding status of geode. Used to indicate busy state, modal 
state for applications. Applications and the UI should use 
**WinSetGeodePtrImage** to set the image. 

PIL_5  
PIL_GADGET  
Gadget level. Used for visible gadgets within windows, such as 
text object, control points, etc. Applications and the UI should 
use **WinSetGeodePtrImage** to set the image.

PIL_7  
PIL_WINDOW  
Window level. Background cursor to use. Applications and the 
UI should use **WinSetGeodePtrImage** to set the image.

PIL_DEFAULT  
Default pointer.

**Library:** win.def

----------
#### PtrImageValue
    PtrImageValue       etype word
        PIV_NONE                    enum PtrImageValue, 0
        PIV_VIDEO_DRIVER_DEFAULT    enum PtrImageValue
        PIV_UPDATE                  enum PtrImageValue

Enumerated type passed as an alternative to an optr to a PointerDef.

PIV_NONE      
No ptr image requested for level. Important: Keep the value of 
this enumerated constant to 0, so that a null optr results in no 
ptr image being requested.

PIV_VIDEO_DRIVER_DEFAULT  
Use video driver default ptr image.

PIV_UPDATE  
Re-write current highest priority ptr image to the video driver. 
Useful when changing PointerDef at previous optr, changing 
screens.

**Library:** win.def

----------
#### QuickSortParameters
    QuickSortParameters             struct
        QSP_compareCallback     fptr    ; Compare two elements
        ;
        ;   Pass:
        ;       ds:si       - first array element
        ;       es:di       - second array element
        ;       bx          - parameter passed to ArrayQuickSort
        ;   Return:
        ;       flags set so caller can jl, je, or jg
        ;       according as first element is less than,
        ;       equal to, or greater than the second.
        ;   Destroyed:
        ;       ax, bx, cx, dx, di, si
        ;
        QSP_lockCallback        fptr    ; Lock an element (segment = 0, for none)
        ;
        ;   Pass:
        ;       ds:si       - array element to lock
        ;       bx          - parameter passed to ArrayQuickSort
        ;   Return:
        ;       nothing
        ;   Destroyed:
        ;       nothing
        ;
        QSP_unlockCallback      fptr    ; Unlock an element (segment = 0, for none)
        ;
        ;   Pass:
        ;       ds:si       - array element to unlock
        ;       bx          - parameter passed to ArrayQuickSort
        ;   Return:
        ;       nothing
        ;   Destroyed:
        ;       nothing
        ;
        QSP_insertLimit         word
        QSP_medianLimit         word
        ;
        ; These are used internally by the quicksort algorithm and should not
        ; be set by the caller.
        ;
        QSP_nLesser             word
        QSP_nGreater            word
        align                   word
    QuickSortParameters             ends

*QSP_insertLimit* stores the size of the list below which we choose to use 
insertion sort and not quicksort.

*QSP_medianLimit* stores the size of list below which we no longer choose the 
median but instead use the first key.

*QSP_nLesser* and *QSP_nGreater* store the number of elements in the lesser 
and greater list parts. This is used internally by the quicksort algorithm.

**Library:** chunkarr.def

----------
#### QuitLevel
    QuitLevel       etype word
        QL_BEFORE_UI            enum QuitLevel
        QL_UI                   enum QuitLevel
        QL_AFTER_UI             enum QuitLevel
        QL_DETACH               enum QuitLevel
        QL_AFTER_DETACH         enum QuitLevel

QL_BEFORE_UI  
Quit message sent out before MSG_META_QUIT messages are 
sent to the items on the active list. 

QL_UI  
Default handler for this method sends MSG_META_QUIT to the 
application object for the process.

QL_AFTER_UI  
Quit message sent out before MSG_META_DETACH is sent to 
the process.

QL_DETACH  
Default handler for this method sends MSG_META_DETACH to 
the process.

QL_AFTER_DETACH  
Default handler for this method doesn't really do anything. 
Why is it still around? You'll understand when you're older.

**Library:** Objects/metaC.def

----------
#### RandomGenInitFlags
    RandomGenInitFlags      record
        RGIF_USE_SEED           :1
        RGIF_GENERATE_SEED      :1
                                :6
    RandomGenInitFlags      end

**Library:** math.def

----------
#### RangeEnumFlags
    RangeEnumFlags      record
        REF_ALL_CELLS           :1  ; Set: callback for all cells.
        REF_NO_LOCK             :1  ; Set: callback will lock/unlock cells.
        REF_ROW_FLAGS           :1  ; Set: get row flags when calling back
        REF_MATCH_ROW_FLAGS     :1  ; Set: callback for cells w/matching row 
                                    ; flags
        ;
        ; These next ones are returned from the callback routine.
        ;
        REF_CELL_ALLOCATED      :1  ; Set: The callback routine allocated the 
                                    ; cell for which the callback occurred.
        REF_CELL_FREED:1            ; Set: The callback routine freed the cell 
                                    ; for which the callback occurred.
        REF_OTHER_ALLOC_OR_FREE :1  ; Set: The callback routine may have 
                                    ; allocated or freed a cell other than the 
                                    ; one for which the callback occurred.
        REF_ROW_FLAGS_MODIFIED  :1  ; Set: The callback routine changed 
                                    ; the row flags
    RangeEnumFlags      end

**Library:** cell.def

----------
#### RangeEnumParams
    RangeEnumParams     struct
        REP_callback        fptr.far    ;routine to call
        REP_bounds          Rectangle   ;cells to enumerate
        ;
        ; Stuff below this point is filled in by RangeEnum() and can be
        ; used by the callback.
        ;
        REP_rowFlags        word        ;current row flags
        ;
        ; Stuff below this point is setup by RangeEnum(). Applications don't
        ; need to worry about it.
        ;
        REP_cfp             fptr.CellFunctionParameters
        ;
        ; Stuff below this point is only used with REF_MATCH_ROW_FLAGS
        ;
        REP_matchFlags      word        ;flags to match
        REP_flagRow         word        ;row we locked for flags
    RangeEnumParams     ends

This structure is used most often by the **RangeEnum** routine. In this case, 
the structure defines how the enumeration will occur.

Occasionally, however, an empty **RangeEnumParams** structure may be 
passed along with the **CellGetExtent** routine. In that case, the routine will 
fill in the *REP_bounds* entry.

*REP_callback* stores the routine to perform the enumeration.

*REP_bounds* stores the range of the cells to perform the enumeration on.

*REP_rowFlags* stores the "row flags" associated with a specific cell. During 
the enumeration, this entry holds the row flags of the most recently processed 
cell. These flags (4 bits in total) are able to provide custom information about 
cells.

*REP_cfp* and *REP_matchFlags* are set up automatically by **RangeEnum**. 
(*REP_cfp* stores the address of the **CellFunctionParameters** structure.)

**Library:** cell.def

----------
#### RangeInsertParams
    RangeInsertParams           struct
        RIP_bounds          Rectangle
        RIP_delta           Point
        RIP_cfp             dword
    RangeInsertParams           ends

This structure is used by the **RangeInsert** routine, which shifts a group of 
cells from one position to another.

*RIP_bounds* stores the range of cells to shift.

*RIP_delta* stores the Point value which specifies the horizontal and vertical 
distance to shift the group of cells.

*RIP_cfp* stores the address of the **CellFunctionParameters** structure; this 
entry is set up automatically by the routine.

**Library:** cell.def

----------
#### RangeSortCellExistsFlags
    RangeSortCellExistsFlags            record
                                    :6      ; Unused bits
        RSCEF_SECOND_CELL_EXISTS    :1      ; Set: Second cell exists
        RSCEF_FIRST_CELL_EXISTS     :1      ; Set: First cell exists
    RangeSortCellExistsFlags            end

**Library:** cell.def

----------
#### RangeSortError
    RangeSortError      etype word, 0, 1
        RSE_NO_ERROR            enum RangeSortError
        RSE_UNABLE_TO_ALLOC     enum RangeSortError

RSE_NO_ERROR  
No error, the sort was successful. 

RSE_UNABLE_TO_ALLOC  
The sorting code was unable to allocate the temporary block it 
needs to sort the data.

**Library:** cell.def

----------
#### RangeSortFlags
    RangeSortFlags      record
        RSF_SORT_ROWS           :1  ; Set: Sort rows
        RSF_SORT_ASCENDING      :1  ; Set: Sort in ascending order
        RSF_IGNORE_CASE         :1  ; Set: Ignore case in string compares
                                :4
        RSF_IGNORE_SPACES       :1  ; Set: Ignore spaces & punctuation
                                    ; NOTE: this is not supported directly
                                    ; by the Cell library, but is placed
                                    ; here for the convenience of apps.
    RangeSortFlags      end

**Library:** cell.def

----------
#### RangeSortParams
    RangeSortParams     struct
        RSP_range           Rectangle
        RSP_active          Point
        RSP_callback        dword       ; Comparison routine
        ;
        ; Callback is defined as:
        ;   PASS:       ds:si   = Pointer to first cells data
        ;               es:di   = Pointer to second cells data
        ;               ax      = RangeSortCellExistsFlags
        ;               ss:bx   = Parameters passed to RangeSort
        ;   RETURN:     Flags set for comparison of the two cells
        ;   DESTROYED: cx, dx, di, si, bp
        ;
        RSP_flags           RangeSortFlags
        align               word
        ;
        ; The rest is used in RangeSort and should be ignored.
        ;
        RSP_cfp             dword
        RSP_sourceChunk     word
        RSP_destChunk       word
        RSP_base            word
        RSP_lockedEntry     dword
        RSP_cachedFlags     byte
        align               word
    RangeSortParams     ends

*RSP_range* stores the rectangular range to conduct the sort on.

*RSP_active* stores the cell in the row/column that the current sort is acting 
upon.

*RSP_flags* stores the **RangeSortFlags** used in the sorting operation.

*RSP_cfp* stores the **CellFunctionParameters**.

*RSP_sourceChunk* stores the source row chunk for swapping.

*RSP_destChunk* stores the destination chunk for swapping.

*RSP_base* stores the base row/column for sort block.

*RSP_lockedEntry* stores the entry that is currently locked. If the segment is 
-1, nothing is locked.

*RSP_cachedFlags* stores the flags (carry set if cell exists).

**Library:** cell.def

----------
#### RecalcSizeArgs
    RecalcSizeArgs      record
        RSA_CHOOSE_OWN_SIZE         :1
        RSA_SUGGESTED_SIZE          :15
    RecalcSizeArgs      end

RSA_CHOOSE_OWN_SIZE  
Geometry manager wants object to choose its own size, 
typically objects will use current size if any, or choose an initial 
size, is coming up for the first time.

RSA_SUGGESTED_SIZE  
Suggested size to use, if above bit is not set.

**Library:** Objects/visC.def

----------
#### Rectangle
    Rectangle           struct
        R_left      sword
        R_top       sword
        R_right     sword
        R_bottom    sword
    Rectangle           ends

This is the standard structure for a rectangle in GEOS.

**Library:** graphics.def

----------
#### RectDWFixed
    RectDWFixed     struct
        RDWF_left       DWFixed
        RDWF_top        DWFixed
        RDWF_right      DWFixed
        RDWF_bottom     DWFixed
    RectDWFixed     ends
    
**Library:** bitmap.def

----------
#### RectDWord
    RectDWord       struct
        RD_left         sdword
        RD_top          sdword
        RD_right        sdword
        RD_bottom       sdword
    RectDWord       ends

This is the standard structure for a rectangle in extended coordinates.

**Library:** graphics.def

----------
#### RectRegion
    RectRegion          struct
        RR_y1M1     word
        RR_eo1      word EOREGREC
        RR_y2       word
        RR_x1       word
        RR_x2       word
        RR_eo2      word EOREGREC
        RR_eo3      word EOREGREC
    RectRegion          ends

This structure stores a rectangular region.

**Library:** graphics.def

----------
#### RectWWFixed
    RectWWFixed     struct
        RWWF_left       WWFixed
        RWWF_top        WWFixed
        RWWF_right      WWFixed
        RWWF_bottom     WWFixed
    RectWWFixed     ends

**Library:** grobj.def

----------
#### RefElementHeader
    RefElementHeader        struct
        REH_refCount            WordAndAHalf
    RefElementHeader        ends

This structure defines a header for an element of a fixed size.

**Library:** chunkarr.def

----------
#### Region
    Region  struct
        R_data      word
    Region  ends
    EOREGREC        =   8000h

This structure stores a region of a graphics coordinate space. A region is of 
arbitrary length and consists of a series of word-length values. 

Regions are described in terms of a rectangular array (thus the similarity to 
bitmaps). Instead of specifying an on/off value for each pixel, however, 
regions assume that the area will be fairly undetailed and that the data 
structure can thus be treated in the manner of a sparse array. Only the cells 
in which the color value of a row changes are recorded. The tricky part here 
is keeping in mind that when figuring out whether or not a row is the same 
as a previous row; the system works its way up from the bottom, so that you 
should compare each row with the row beneath it to determine whether it 
needs an entry.

The easiest region to describe is the null region, which is a special case 
described by a single word with the value EOREGREC (which stands for *E*nd 
*O*f *REG*ion *REC*ord value). Describing a non-null region requires several 
numbers.

The first four words of the region (starting with R_data) give the 
(rectangular) bounds of the region. What follows is a series of one or more 
numbers. Each word-length entry describes a row, specifying which pixels of 
that row are part of the region. The only rows which need to be described are 
those which are different 

**Library:** graphics.def

----------
#### RegionFillRule
    RegionFillRule      etype byte
        RFR_ODD_EVEN    enum RegionFillRule     ; 0 = odd-even rule
        RFR_WINDING     enum RegionFillRule     ; 1 = winding rule

**Library:** graphics.def

----------
#### ReleaseNumber
    ReleaseNumber       struct
        RN_major            word
        RN_minor            word
        RN_change           word
        RN_engineering      word
    ReleaseNumber       ends

This structure stores the release number (version) of a file, document or 
geode.

*RN_major* stores the major release number. Different major release numbers 
signify a considerable version difference.

*RN_minor* stores the minor release version. Different minor release numbers 
typically mean a minor version "tweaking" of the system.

*RN_change* and *RN_engineering* are internal release numbers that should not 
need to be examined or changed.

**Library:** geode.def

----------
#### ReplaceAllFromOffsetFlags
    ReplaceAllFromOffsetFlags           record
        RAFOF_CONTINUING_REPLACE    :1
        RAFOF_HAS_UNDO              :1
                                    :14
    ReplaceAllFromOffsetFlags           end

RAFOF_CONTINUING_REPLACE  
Set if this message was generated to continue a replace all sent 
to a different object.

RAFOF_HAS_UNDO  
Set if this action will be undoable - mainly used for 
error-checking, to ensure that all objects involved in a 
ReplaceAll are undoable.

**Library:** Objects/vTextC.def

----------
#### ReplaceAllFromOffsetStruct
    ReplaceAllFromOffsetStruct          struct
        RAFOS_data              hptr.SearchReplaceStruct
        RAFOS_startOffset       dword
        RAFOS_flags             ReplaceAllFromOffsetFlags
    ReplaceAllFromOffsetStruct          ends

*RAFOS_data* stores a pointer to the replace-all data. The data is organized in 
the following format:
**SearchReplaceStruct**<>  
data - Null-Terminated Search string  
data - Null-Terminated Replace string  
Note: The sender of this message is responsible for freeing the passed 
**SearchReplaceStruct**. 

*RAFOS_startOffset* stores the offset in this object to begin the replace all 
operation.

*RAFOS_flags* stores flags that are set internally by the text object; do not set 
them.

**Library:** Objects/vTextC.def

----------
#### ReplaceAllInRangeStruct
    ReplaceAllInRangeStruct         struct
        RAIRS_data          hptr.SearchReplaceStruct
        RAIRS_range         VisTextRange <>
    ReplaceAllInRangeStruct         ends

*RAIRS_data* stores a pointer to the replace-all data. The data is organized in 
the following format:
**SearchReplaceStruct**<>  
data - Null-Terminated Search string  
data - Null-Terminated Replace string  
Note: The sender of this message is responsible for freeing the passed 
SearchReplaceStruct. 

**Library:** Objects/vTextC.def

----------
#### ReplaceItemMonikerFlags
    ReplaceItemMonikerFlags         record
        RIMF_NOT_ENABLED        :1
                                :15
    ReplaceItemMonikerFlags         end

RIMF_NOT_ENABLED  
Ensure that the item we are setting the moniker for will be 
disabled while visible.

**Library:** Objects/gDListC.def

----------
#### ReplaceItemMonikerFrame
    ReplaceItemMonikerFrame         struct
        RIMF_source         dword
        RIMF_sourceType     VisMonikerSourceType
        even
        RIMF_dataType       VisMonikerDataType
        even
        RIMF_length         word
        RIMF_width          word
        RIMF_height         word
        RIMF_itemFlags      ReplaceItemMonikerFlags
        RIMF_item           word
    ReplaceItemMonikerFrame         ends

*RIMF_source* stores a pointer to the source moniker. This pointer may be an 
optr, hptr, or fptr, depending on the *RIMF_sourceType*.

*RIMF_sourceType* defines the type of pointer contained in *RIMF_source*.

*RIMF_dataType* defines whether the source is a VisMoniker, text string, 
graphics string, or GeodeToken.

*RIMF_length* stores the size (in bytes) of the source. (This value is not used 
for VMST_OPTR.) If the data type is VMDT_TEXT and *RIMF_length* is 0, the 
text is assumed to be null-terminated. If the data type is VMDT_GSTRING 
and *RIMF_length* is 0, the length of the gstring is computed by scanning the 
gstring.

*RIMF_width* stores the width of the graphics string if the data type is 
VMDT_GSTRING. If 0, the width of the gstring is computed by scanning the 
gstring.

*RIMF_height* stores the height of the graphics string if the data type is 
VMDT_GSTRING. If 0, the height of the gstring is computed by scanning the 
gstring.

*RIMF_itemFlags* stores the item flags for the function.

*RIMF_item* stores the position of the item whose moniker you're setting.

**Library:** Objects/gDListC.def

----------
#### ReplaceVisMonikerFrame
    ReplaceVisMonikerFrame          struct
        RVMF_source             dword
        RVMF_sourceType         VisMonikerSourceType
        even
        RVMF_dataType           VisMonikerDataType
        even
        RVMF_length             word
        RVMF_width              word
        RVMF_height             word
        RVMF_updateMode         VisUpdateMode
        even
    ReplaceVisMonikerFrame          ends

This structure is used by MSG_GEN_REPLACE_VIS_MONIKER to store the 
parameters used in that operation.

*RVMF_source* stores a pointer to the source moniker. This pointer may be an 
optr, hptr, or fptr, depending on the *RVMF_sourceType*.

*RVMF_sourceType* defines the type of pointer contained in *RVMF_source*.

*RVMF_dataType* defines whether the source is a VisMoniker, text string, 
graphics string, or GeodeToken.

*RVMF_length* stores the size (in bytes) of the source. (This value is not used 
for VMST_OPTR.) If the data type is VMDT_TEXT and *RVMF_length* is 0, the 
text is assumed to be null-terminated. If the data type is VMDT_GSTRING 
and *RVMF_length* is 0, the length of the gstring is computed by scanning the 
gstring.

*RVMF_width* stores the width of the graphics string if the data type is 
VMDT_GSTRING. If 0, the width of the gstring is computed by scanning the 
gstring.

*RVMF_height* stores the height of the graphics string if the data type is 
VMDT_GSTRING. If 0, the height of the gstring is computed by scanning the 
gstring.

*RVMF_updateMode* stores the visual update mode to define when to show the 
new moniker.

**Library:** Objects/genC.def

----------
#### ReplaceWithGraphicParams
    ReplaceWithGraphicParams            struct
        RWGP_range              VisTextRange    ;range to replace
        RWGP_pasteFrame         word            ;ptr to frame if quick paste.
                                                ;0 otherwise.
        RWGP_sourceFile         word            ;source vm file
        RWGP_graphic            VisTextGraphic
    ReplaceWithGraphicParams            ends

**Library:** Objects/vTextC.def

----------
#### ReplaceWithHWRData
    ReplaceWithHWRData      struct
        RWHWRD_range            VisTextRange <>
        RWHWRD_context          HWRContext <>
    ReplaceWithHWRData      ends

*RWHWRD_range* stores the range to replace. This range may start beyond the 
end of the text. If so, spaces should be appended to the text.

*RWHWRD_context* stores the context in which the hand writing recognition 
data was added.

**Library:** Objects/gPenICC.def

----------
#### RequestedViewArea
    RequestedViewArea       etype byte
        RVA_NO_AREA_CHOICE  enum RequestedViewArea  ;no choice made here
        RVA_X_SCROLLER_AREA enum RequestedViewArea  ;put with x scroller
        RVA_Y_SCROLLER_AREA enum RequestedViewArea  ;put with y scroller
        RVA_LEFT_AREA       enum RequestedViewArea  ;put in left area
        RVA_TOP_AREA        enum RequestedViewArea  ;put in top area
        RVA_RIGHT_AREA      enum RequestedViewArea  ;put in right area
        RVA_BOTTOM_AREA     enum RequestedViewArea  ;put in bottom area

**Library:** Objects/genC.def

----------
#### RGBDelta
    RGBDelta        struct
        RGBD_red        sbyte
        RGBD_green      sbyte
        RGBD_blue       sbyte
    RGBDelta        ends

**Library:** color.def

----------
#### RGBValue
    RGBValue        struct
        RGB_red         byte
        RGB_green       byte
        RGB_blue        byte
    RGBValue        ends

**Library:** color.def

----------
#### RGCFeatures
    RGCFeatures     record
        RGCF_GRID_SPACING       :1
        RGCF_SNAP_TO_GRID       :1
        GRCF_SHOW_GRID          :1
    RGCFeatures     end

**Library:** ruler.def

----------
#### RowBlockList
    RowBlockList        struct
        RBL_blocks          nptr N_ROW_BLOCKS dup (0)
    RowBlockList        ends

**Library:** cell.def

----------
#### RSCCFeatures
    RSCCFeatures        record
        RSCCF_SHOW_VERTICAL         :1
        RSCCF_SHOW_HORIZONTAL       :1
        RSCCF_SHOW_RULERS           :1
    RSCCFeatures        end

**Library:** ruler.def

----------
#### RSCCToolboxFeatures
    RSCCToolboxFeatures         record
    RSCCToolboxFeatures         end

**Library:** ruler.def

----------
#### RTCFeatures
    RTCFeatures     record
        RTCF_DEFAULT        :1
        RTCF_SPREADSHEET    :1
        RTCF_INCHES         :1
        RTCF_CENTIMETERS    :1
        RTCF_POINTS         :1
        RTCF_PICAS          :1
    RTCFeatures     end

**Library:** ruler.def

----------
#### RTCToolboxFeatures
    RTCToolboxFeatures      record
        RTCTF_DEFAULT           :1
        RTCTF_SPREADSHEET       :1
        RTCTF_INCHES            :1
        RTCTF_CENTIMETERS       :1
        RTCTF_POINTS            :1
        RTCTF_PICAS             :1
    RTCToolboxFeatures      end

**Library:** ruler.def

----------
#### RulerGridNotificationBlock
    RulerGridNotificationBlock              struct
        RGNB_gridSpacing                WWFixed
        RGNB_gridOptions                GridOptions
    RulerGridNotificationBlock              ends

**Library:** ruler.def

----------
#### RulerGuideControlFeatures
    RulerGuideControlFeatures           record
        RGCF_HV                 :1
        RGCF_LIST               :1
        RGCF_POSITION           :1
        RGCF_DELETE             :1
    RulerGuideControlFeatures           end

**Library:** ruler.def

----------
#### RulerShowControlAttributes
    RulerShowControlAttributes              record
        RSCA_SHOW_VERTICAL              :1
        RSCA_SHOW_HORIZONTAL            :1
                                        :14
    RulerShowControlAttributes              end

**Library:** ruler.def

----------
#### RulerTypeNotificationBlock
    RulerTypeNotificationBlock          struct
        RTNB_type       VisRulerType
    RulerTypeNotificationBlock          ends

**Library:** ruler.def

----------
#### RulerViewAttributes
    RulerViewAttributes         record
        RVA_HORIZONTAL      :1
                            :7
    RulerViewAttributes         end

**Library:** ruler.def

[Structures H-M](asmstrhm.md) <-- [Table of Contents](../asmref.md) &nbsp;&nbsp; --> [Structures S-S](asmstrss.md)


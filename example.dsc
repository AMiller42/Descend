# Descend @Descend
---
#2 An Example @Example

@Paragraph1
This is an example of a page written in Descend.  It has a markdown version and an HTML version.
This is the markdown version. It is designed to include every example of Descend formatting, and
give an overview of the available features. This paragraph is ended with the `⁋` character.⁋
@Paragraph2
This paragraph includes [a link](https://example.com), [a button]{say("Hello, World!")}, *_~=^!text formatting!^=~_*, and ``a bit of code.``
It is ended by two newlines.

@Blockquote1
> This is a blockquote. It starts with the `>` character and ends with the `<` character.

This means that you can put multiple paragraphs inside of it. <

@Ordered1
. This is a numbered list.
. It can be started a couple ways.
. You can use `.` before each line.
. You can also use `1. 2. 3. etc.` if you want.

@Unordered1
* This is an unordered list.
* It is started with `*`.
@Unordered2
+ You can also use `+` or `-`
@Unordered3
- Switching starting character will start a new list.

`` @Code1
This is a codeblock.
It starts with some number of backticks on their own line,
and ends with the same number of backticks on their own line.
That means that a line containing `` won't break the codeblock formatting.
``

#3 Tables @Tables

@Table1
This|is|a|table
-
This|is|the|body
Here|is|another|line

@Table2
This|
is|
also|
a|
table|

@Table3
You|can|justify
<|_|>
This|The|This
side|middle|side
uses|uses|uses
`<`|`_`|`>`

#4 Dicionary Lists @Dicts

@Dict1
This is the key
:This is the first value
:This is the second value
:And here is a third

#5 Miscellaneous Other Things @Misc

@Task1
-[] These are task lists
-[x] They can be checked
-[] Or they can be unchecked

@Emojis
You :clap: can :clap: also :clap: insert :clap: emojis :clap: using :clap: the :clap: shortcode.  
You can also use shortcodes to insert other characters and symbols, e.g. :pi: :phi: :8721: :8719:

@Textarea1
(Textareas can have some default, over-writable text.)

#3 Scripts @Scripts
Descend also has some built-in scripting. These scripts can be standalone, 
where they can be run automatically or be called by other scripts, 
or they can be attached to a button and be run when the button is clicked.

For example, when clicked this button will delete the contents of the page: [Click Me!]{del(this); new("img", src="https://i.stack.imgur.com/o2cOC.gif")}

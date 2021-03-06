require "lazytree"
require "lxptree"
require "xmliter"

-- wget an xhtml document
l0 = lazytree.parsefile("index.html")
-- l0 = lxptree.parsefile("index.html")

local ftable
ftable = {
  a=function (a)
      if a.attr.href then
        print("href", a.attr.href)
      end
      xmliter.switch_c(a, ftable)
    end
}

ftable[true]=ftable

xmliter.switch_c(l0, ftable)

-- os.execute("ps ux | grep lua | grep traces | grep -v grep")

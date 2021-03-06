/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

function test() {
  // There should be one tab when we start the test
  let [origTab] = gBrowser.visibleTabs;
  is(gBrowser.visibleTabs.length, 1, "there is one visible tab");
  let testTab = gBrowser.addTab();
  is(gBrowser.visibleTabs.length, 2, "there are now two visible tabs");

  // Check the context menu with two tabs
  updateTabContextMenu(origTab);
  is(document.getElementById("context_closeTab").disabled, false, "Close Tab is enabled");
  is(document.getElementById("context_reloadAllTabs").disabled, false, "Reload All Tabs is enabled");

  // Hide the original tab.
  gBrowser.selectedTab = testTab;
  gBrowser.showOnlyTheseTabs([testTab]);
  is(gBrowser.visibleTabs.length, 1, "now there is only one visible tab");
  
  // Check the context menu with one tab.
  updateTabContextMenu(testTab);
  is(document.getElementById("context_closeTab").disabled, false, "Close Tab is enabled when more than one tab exists");
  is(document.getElementById("context_reloadAllTabs").disabled, true, "Reload All Tabs is disabled");
  
  // Add a tab that will get pinned
  // So now there's one pinned tab, one visible unpinned tab, and one hidden tab
  let pinned = gBrowser.addTab();
  gBrowser.pinTab(pinned);
  is(gBrowser.visibleTabs.length, 2, "now there are two visible tabs");

  // Check the context menu on the unpinned visible tab
  updateTabContextMenu(testTab);
  is(document.getElementById("context_closeOtherTabs").disabled, true, "Close Other Tabs is disabled");

  // Show all tabs
  let allTabs = [tab for each (tab in gBrowser.tabs)];
  gBrowser.showOnlyTheseTabs(allTabs);

  // Check the context menu now
  updateTabContextMenu(testTab);
  is(document.getElementById("context_closeOtherTabs").disabled, false, "Close Other Tabs is enabled");
  
  gBrowser.removeTab(testTab);
  gBrowser.removeTab(pinned);
}
